#pragma once
#include <chrono>
#include <format>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include "HanoiModel.hpp"
#include "HanoiController.hpp"

using namespace ftxui;

class HanoiPanel{
private:
    HanoiModel model;
    HanoiController ctrl{model};

    int left_width = 26;
    std::thread auto_thread;

    Component disc_slider;
    Component speed_slider;
    Component solve_btn;
    Component auto_btn;
    Component prev_btn;
    Component next_btn;
    Component left_panel;
    Component right_panel;
    Component split;


    Color diskColor(size_t idx) const{
        static const Color p[] = {
            Color::Red, Color::Yellow, Color::Green, Color::Cyan,
            Color::Blue, Color::Magenta, Color::White,
            Color::RedLight, Color::GreenLight, Color::BlueLight,
            Color::YellowLight, Color::MagentaLight,
        };
        return p[idx % 12];
    }

    Element renderPeg(size_t pegIdx) const{
        size_t n = model.disk_count;
        const auto& rod = model.GetRod(pegIdx);

        size_t ids[12] = {};
        size_t cnt = 0;
        for (auto ring : rod){
            ids[cnt++] = ring.size;
        }

        size_t field = 2 * n;
        Elements rows;

        for (size_t row = 0; row < n; ++row) {
            size_t slot = (n - 1) - row;
            if (slot < cnt) {
                size_t diskId = ids[slot];
                size_t pad = n - (diskId + 1);
                rows.push_back(hbox({
                    text(std::string(pad, ' ')),
                    text(std::string(2 * (diskId + 1) + 1, ' ')) | bgcolor(diskColor(diskId)),
                    text(std::string(pad, ' ')),
                }));
            } else {
                rows.push_back(hbox({
                    text(std::string(n, ' ')),
                    text("│") | color(Color::GrayDark),
                    text(std::string(n, ' ')),
                }));
            }
        }

        rows.push_back(text(std::string(field + 1, '-')) | color(Color::GrayLight));
        static const char* lbl[] = {" A ", " B ", " C "};
        rows.push_back(text(lbl[pegIdx]) | center | dim);
        return vbox(rows) | center;
    }

    Element renderBoard() const{
        if (!model.solved){
            return text("Задайте количество блинов и нажмите «Решить»")| center | dim | flex;
        }

        Element fin = text("");
        if(model.current_step == model.totalSteps()){
            fin = text("Решено!") | color(Color::Green) | bold;
        }
        return vbox({
            hbox({
                renderPeg(0) | flex,
                separator(),
                renderPeg(1) | flex,
                separator(),
                renderPeg(2) | flex,
            }) | flex,
            separator(),
            hbox({
                text(std::format(" Шаг {}/{} ",model.current_step, model.totalSteps())) | dim,
                filler(),
                fin,
                filler(),
                text(std::format(" {} блинов ", model.disk_count)) | dim,
            }),
        }) | flex;
    }

    void buildComponents(){
        auto button_style = ButtonOption::Animated(Color::Default, Color::White, Color::Default, Color::GrayDark);

        auto slider_opt = SliderOption<int>();
        slider_opt.value = &model.disk_count;
        slider_opt.min = 1;
        slider_opt.max = 10;
        slider_opt.increment = 1;
        slider_opt.on_change = [&] {
            model.auto_playing = false;
            model.solved = false;
            model.current_step = 0;
        };
        disc_slider = Slider(slider_opt);

        auto speed_opt = SliderOption<int>();
        speed_opt.value = &model.auto_speed;
        speed_opt.min = 1;
        speed_opt.max = 100;
        speed_opt.increment = 5;
        speed_slider = Slider(speed_opt);

        solve_btn = Button("Решить", [&]{
            model.auto_playing = false;
            ctrl.onSolve();
        }, button_style);

        prev_btn = Button("Назад", [&]{
            model.auto_playing = false;
            ctrl.onPrev();
        }, button_style);

        next_btn = Button("Вперёд", [&]{
            model.auto_playing = false;
            ctrl.onNext();
        }, button_style);

        auto_btn = Button("Старт/Стоп", [&]{
            if (!model.solved){
                return;
            }
            model.auto_playing = !model.auto_playing;
            if (model.auto_playing) {
                if (model.current_step >= model.totalSteps())
                    model.current_step = 0;
                model.last_auto_step = std::chrono::system_clock::now();
            }
        }, button_style);

        auto left_inner = Container::Vertical({
            disc_slider, speed_slider, solve_btn, auto_btn
        });

        left_panel = Renderer(left_inner, [&, left_inner] {
            return vbox({
                text("Блинов") | bold,
                hbox({
                    text(std::format(" {} ",
                        model.disk_count)),
                        disc_slider->Render()
                    }),
                separator(),
                text("Скорость") | bold,
                hbox({
                    text(std::format(" {} ", model.auto_speed)),
                    speed_slider->Render()
                }),
                separator(),
                solve_btn->Render(),
                separator(),
                auto_btn->Render(),
                separator(),
                text(model.solved ? std::format("Всего ходов: {}", model.totalSteps()) : "") | dim,
            });
        });

        auto ctrl_bar = Container::Horizontal({prev_btn, next_btn});
        right_panel = Renderer(ctrl_bar, [&, ctrl_bar] {
            if (model.auto_playing) {
                if (model.current_step >= model.totalSteps()) {
                    model.auto_playing = false;
                } else {
                    auto now = std::chrono::system_clock::now();
                    if (now - model.last_auto_step >= model.autoInterval()) {
                        model.last_auto_step = now;
                        ctrl.onNext();
                    }
                }
            }
            return vbox({
                renderBoard() | flex,
                separator(),
                ctrl_bar->Render() | center,
            });
        });

        split = ResizableSplitLeft(left_panel, right_panel, &left_width);
    }

public:
    Component build(){
        buildComponents();
        return split;
    }
};
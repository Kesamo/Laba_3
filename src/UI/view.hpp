#pragma once
#include <thread>
#include <chrono>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;
using namespace std::chrono_literals;

class AppUI{
private:
    int tab_idx = 0;

    std::vector<std::string> tab_names = {
        " Ханойские башни ",
        " Стек ",
        " Дек ",
        " Матрица ",
    };

    ButtonOption ButtonStyle() {
        return ButtonOption::Animated(
            Color::Default,
            Color::White,
            Color::Default,
            Color::GrayDark     
        );
    }

    Component tab_menu;
    Component tab_content;
    Component exit_button;
    Component main_renderer;

public:
    void Run(){
        auto screen = App::Fullscreen();

        auto tab_opt = MenuOption::HorizontalAnimated();
        tab_opt.underline.SetAnimationFunction(animation::easing::BackOut);
        tab_opt.underline.SetAnimationDuration(250ms);
        tab_menu = Menu(&tab_names, &tab_idx, tab_opt);

        tab_content = Container::Tab({ 
        }, &tab_idx);

        exit_button = Button("Выход", screen.ExitLoopClosure(), ButtonStyle());

        auto top = Container::Horizontal({
            tab_menu,
            exit_button
        });

        auto root = Container::Vertical({
            top,
            tab_content
        });

        main_renderer = Renderer(root, [&]{
            return vbox({
                hbox({
                    tab_menu->Render() | flex,
                    exit_button->Render(),
                }),
                separator(),
                tab_content->Render() | flex,
            })| bgcolor(Color::Black) | border;
        });

        Loop loop(&screen, main_renderer);
            while (!loop.HasQuitted()) {
            screen.RequestAnimationFrame();
            loop.RunOnce();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
};
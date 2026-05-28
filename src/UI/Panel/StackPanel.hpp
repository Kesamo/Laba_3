#pragma once
#include <format>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include "Stack/StackAliases.hpp"
#include "MutableSequenceArray.hpp"

using namespace ftxui;

class StackPanel {
private:
    ArrayStack<int> stack;

    std::string input  = "";
    std::string result = "";
    int length_split = 30;

    Component input_comp;
    Component push_btn, pop_btn, top_btn, clear_btn;
    Component left_panel, right_panel, split;
    Component root;

    void doPush() {
        if (input.empty()) {
            result = "Введите число";
            return;
        }
        stack.push(std::stoi(input));
        result = std::format("push({})  размер={}", input, stack.size());
        input  = "";

    }

    void doPop() {
        if (stack.empty()){
            result = "Стек пуст";
            return;
        }
        result = std::format("pop() = {}  размер={}", stack.pop(), stack.size());
    }

    void doTop() {
        if (stack.empty()){
            result = "Стек пуст";
            return;
        }
        result = std::format("top() = {}", stack.top());
    }

    void doClear() {
        while(!stack.empty()){
            stack.pop();
        }
        result = "Стек очищен";
    }

    Element renderStack() const {
        if (stack.empty())
            return text("Пусто") | center | dim | flex;

        int ids[512]; 
        int cnt = 0;
        for (auto v : stack){
            ids[cnt++] = v;
        }

        Elements rows;
        rows.push_back(text("Вершина") | dim);

        for (int i = cnt - 1; i >= 0; --i) {
            rows.push_back(text(std::to_string(ids[i]))| center | border);
        }
        rows.push_back(text("Дно") | dim);
        rows.push_back(separator());
        rows.push_back(text(std::format(" размер: {}", stack.size())) | dim);
        return vbox(rows);
    }

    void buildComponents() {
        auto btn_option = ButtonOption::Animated(Color::Default, Color::White, Color::Default, Color::GrayDark);

        input_comp = Input(&input, "value");

        input_comp |= CatchEvent([&](Event e) {
        if (e.is_character()) {
                char c = e.character()[0];
                if (!std::isdigit(c) && c != '-'){ 
                    return true;
                }
                if (c == '-'){
                    if (!input.empty()) {
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                std::string future = input + c;
                if (future.size() > 10){ 
                    return true;
                }
                int num = std::stoi(future);    
                if (-2147483647 > num > 2147483647){ 
                    return true;
                }
            }
            return false;
        });

        push_btn = Button("Push",[&]{ doPush();}, btn_option);
        pop_btn = Button("Pop",[&]{ doPop();}, btn_option);
        top_btn = Button("Top",[&]{ doTop();}, btn_option);
        clear_btn = Button("Clear",[&]{ doClear();}, btn_option);

        auto left_inner = Container::Vertical({
            input_comp,
            push_btn, 
            pop_btn, 
            top_btn, 
            clear_btn,
        });

        left_panel = Renderer(left_inner, [&, left_inner]{
            return vbox({
                text("Значение") | bold,
                input_comp->Render() | border,
                separator(),
                hbox({ push_btn->Render(),
                    pop_btn->Render()
                }),
                hbox({ top_btn->Render(),
                    clear_btn->Render()
                }),
                separator(),
                paragraph(result) | color(Color::Cyan),
            });
        });

        right_panel = Renderer([&]{
            return vbox({
                renderStack() | flex,
            })| flex;
        });

        split = ResizableSplitLeft(left_panel, right_panel, &length_split);
    }

public:
    Component build() {
        buildComponents();
        return split;
    }
};
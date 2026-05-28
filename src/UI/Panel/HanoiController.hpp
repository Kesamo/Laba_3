#pragma once
#include "HanoiModel.hpp"
#include <ftxui/component/screen_interactive.hpp>

class HanoiController {
    HanoiModel& model;
public:
    HanoiController(HanoiModel& m) : model(m) {}

    void onPrev()  { model.stepBack(); }
    void onNext()  { model.stepForward(); }
    void onSolve() { model.solve(); }
};
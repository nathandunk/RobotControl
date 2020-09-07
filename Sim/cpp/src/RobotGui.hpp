#pragma once

#include <Mahi/Gui.hpp>

using namespace mahi::gui;

class RobotGui : public Application {
public:
    RobotGui():
        Application()
    {

    }

private:
    void update() override {
        ImGui::Begin("Test Gui Window");
        ImGui::Text("Test");
        ImGui::End();
    }
};


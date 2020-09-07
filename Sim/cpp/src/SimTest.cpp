#include <RobotGui.hpp>
#include <thread>

// std::thread gui_thread;
RobotGui gui;

void gui_thread(){
    gui.run();
}

void open_gui() {
    auto thrd = std::thread(gui_thread);
    thrd.detach();
}

void start(){
    open_gui();
}

int main(){
    start();
    while(true){
        
    }
    return 0;
}
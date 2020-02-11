cmake_minimum_required(VERSION 3.13)

# create your C++ project
project(ControlGUI VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(mahi-gui)

# add your include directories
include_directories("include")

# create an app from your source files
add_executable(control_gui "control_gui.cpp")
target_link_libraries(control_gui mahi::gui)

add_executable(serial_test "serial_test.cpp")
# target_link_libraries(control_gui mahi::gui)

# link your app to MEL libaries
# target_link_libraries(my_app 
    # MEL::MEL          # common MEL classes available on all systems
    # MEL::quanser    # needed if using MEL Quanser classes
    # MEL::myo        # needed if using MEL Myo classes
    # MEL::myrio      # needed if using MEL NI myRIO classes
# )

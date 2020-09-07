cmake_minimum_required(VERSION 3.12)

project(RobotSim VERSION 0.1 LANGUAGES C CXX)

include(FetchContent) 
FetchContent_Declare(mahi-robo GIT_REPOSITORY https://github.com/mahilab/mahi-robo.git) 
FetchContent_MakeAvailable(mahi-robo)
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/mahilab/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

include_directories(src)

add_library(robot_sim SHARED src/RobotModel.cpp src/RobotModel.hpp src/RobotParams.hpp src/RobotSim.cpp src/RobotGui.hpp)
target_link_libraries(robot_sim mahi::robo mahi::gui)

add_executable(sim_test src/SimTest.cpp src/RobotModel.cpp src/RobotModel.hpp src/RobotParams.hpp src/RobotGui.hpp)
target_link_libraries(sim_test mahi::robo mahi::gui)

add_executable(gui_test src/gui_test.cpp src/RobotGui.hpp)
target_link_libraries(gui_test mahi::gui)

add_custom_command(TARGET robot_sim POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               $<TARGET_FILE:robot_sim>              
               "${PROJECT_SOURCE_DIR}/../unity/RobotSim/Build/RobotSim_Data/Plugins/")
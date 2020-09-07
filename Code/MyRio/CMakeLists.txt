cmake_minimum_required(VERSION 3.13)

# create your C++ project
project(ControlGUI VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(mahi-daq GIT_REPOSITORY https://github.com/mahilab/mahi-daq)
FetchContent_MakeAvailable(mahi-daq)

add_library(robot_lib "")

file(GLOB_RECURSE ROB_SRC "src/*.cpp")
file(GLOB_RECURSE ROB_HEADERS "include/*.hpp")

target_sources(robot_lib PRIVATE ${ROB_SRC})
target_include_directories(robot_lib PUBLIC ${ROB_HEADERS})

target_link_libraries(robot_lib mahi::daq)

# create an app from your source files
add_executable(rio_robot "rio_robot.cpp")
target_link_libraries(rio_robot mahi::daq)

add_executable(test test.cpp)
target_link_libraries(test robot_lib)
cmake_minimum_required(VERSION 3.13)

# create your C++ project
project(ControlGUI VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(mahi-daq GIT_REPOSITORY https://github.com/mahilab/mahi-daq)
FetchContent_MakeAvailable(mahi-daq)
# add_subdirectory(mahi-gui)

# add your include directories
# include_directories("include")

# create an app from your source files
add_executable(rio_robot "rio_robot.cpp")
target_link_libraries(rio_robot mahi::daq)
cmake_minimum_required(VERSION 3.16.0)

include(FetchContent)

# MAHI DAQ
FetchContent_Declare(mahi-util GIT_REPOSITORY https://github.com/mahilab/mahi-util.git)
FetchContent_MakeAvailable(mahi-util)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(RobotControl)

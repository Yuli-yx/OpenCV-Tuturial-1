cmake_minimum_required(VERSION 3.10)
project(camera_calibration)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 11)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(camera_calibration main.cpp)

target_link_libraries(camera_calibration ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.10)
project(AppleDetection)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(AppleDetection main.cpp)

target_link_libraries( AppleDetection ${OpenCV_LIBS}  )











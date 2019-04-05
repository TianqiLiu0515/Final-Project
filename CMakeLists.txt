cmake_minimum_required(VERSION 3.13)
project(Driving)


set(OpenCV_DIR /Users/tianqi/Downloads/opencv-4.0.1/release)

#find_library(OpenCV)
find_package(OpenCV)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES fish_eye.cpp)
#include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Driving fish_eye.cpp)

target_link_libraries( Driving ${OpenCV_LIBS})
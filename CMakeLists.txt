cmake_minimum_required(VERSION 3.7.2)
project(SemestralkaClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(SemestralkaClient main.cpp Sources/Application.cpp Headers/Application.h Sources/Vypisy.cpp Headers/Vypisy.h Headers/Utilities.h)

cmake_minimum_required(VERSION 3.20)
project(Cpptester)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cpptester
        Datalogger.hpp
        main.cpp)

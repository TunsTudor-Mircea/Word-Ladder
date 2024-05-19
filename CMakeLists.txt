cmake_minimum_required(VERSION 3.27)
project(ExtraCredit3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ExtraCredit3
        Graph.cpp
        Graph.h
        Dictionary.h
        Dictionary.cpp
        Gamemodes.h
        Gamemodes.cpp
        main.cpp
)

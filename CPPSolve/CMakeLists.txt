cmake_minimum_required(VERSION 3.27)
project(CPPSolve)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(CPPSolve
        Game.hpp
        main.cpp
        Solver.cpp
        Solver.hpp
        TTT.cpp
        TTT.hpp
        XtoZero.cpp
        XtoZero.hpp)

cmake_minimum_required(VERSION 4.0)
project(ESRPatcherCLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(ESRPatcherCLI main.cpp
        CmdHandler.hpp
        functions.hpp
        Patcher.cpp)

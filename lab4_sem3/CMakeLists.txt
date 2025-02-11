cmake_minimum_required(VERSION 3.27)
project(labr4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(labr4 main.cpp
        DynamicArray.h
        iterator.h
        GraphParts.h
        Path.h
        Graph.h
        menuFunc.h
)

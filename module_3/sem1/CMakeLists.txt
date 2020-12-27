cmake_minimum_required(VERSION 3.17)
project(sem1)

set(CMAKE_CXX_STANDARD 14)

add_executable(sem1 main.cpp IGraph.h ListGraph.h ListGraph.cpp MatrixGraph.h MatrixGraph.cpp SetGraph.h SetGraph.cpp ArcGraph.h ArcGraph.cpp)
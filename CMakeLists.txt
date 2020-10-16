cmake_minimum_required(VERSION 3.17)
project(TP_homework_AlandSD)

set(CMAKE_CXX_STANDARD 14)

include_directories(project/include)

add_executable(TP_homework_AlandSD
        project/main.cpp
        project/1_4/countdown.cpp
        project/2_3/intersection.cpp
        project/3_2/dek_array.cpp
        project/3_2/dek_list.cpp)
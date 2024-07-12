cmake_minimum_required(VERSION 3.23)
project(labwork_3_stt0504)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(labwork_3_stt0504
        main.cpp
        image.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")

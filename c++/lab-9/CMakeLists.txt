cmake_minimum_required(VERSION 3.23)
project(labwork_9_stt0504)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(labwork_9_stt0504
        allocator.h
        main.cpp
        memory_pool.h
        memory_pool.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static")
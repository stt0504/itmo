cmake_minimum_required(VERSION 3.23)
project(labwork_8_stt0504)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(labwork_8_stt0504
        CCircularBuffer.h
        main.cpp iterator.h CCircularBufferExt.h)
add_subdirectory(tests)

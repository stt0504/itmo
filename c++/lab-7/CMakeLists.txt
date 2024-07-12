cmake_minimum_required(VERSION 3.23)
option(CONSOLE_CHARSET "Set console charset to UTF-16" ON)
project(labwork_7_stt0504)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

if (CONSOLE_CHARSET)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-16>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-16>")
endif ()
add_executable(labwork_7_stt0504
        id3v2parser.cpp
        parser.cpp
        id3v2parser.h
        frames_maps.h
        main.cpp frames_readers.cpp frames_printers.cpp frames_maps.h)

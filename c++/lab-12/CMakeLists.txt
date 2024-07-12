cmake_minimum_required(VERSION 3.23)
project(labwork_12_stt0504)


set(CMAKE_CXX_STANDARD 23)

add_executable(labwork_12_stt0504 main_.cpp database.cpp database_request.cpp)

add_subdirectory(tests)
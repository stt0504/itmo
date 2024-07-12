cmake_minimum_required(VERSION 3.23)
project(labwork-10-stt0504)

set(CMAKE_CXX_STANDARD 23)
include_directories("D:/PROGRAMS/CLion2023.1/curses/PDCurses-3.8")

link_directories("D:/PROGRAMS/CLion2023.1/curses/PDCurses-3.8/wincon")
add_executable(labwork-10-stt0504
        main.cpp WeatherRequest.cpp WeatherRequest.h WeatherPrint.cpp WeatherPrint.h)

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)
target_link_libraries(labwork-10-stt0504 PRIVATE cpr::cpr)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(labwork-10-stt0504 PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(labwork-10-stt0504 PRIVATE pdcurses)
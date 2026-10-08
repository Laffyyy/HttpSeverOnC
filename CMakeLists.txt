# 1. Specify minimum required version of CMake
cmake_minimum_required(VERSION 3.15)


project(WebServer VERSION 1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")

set(SOURCES
    src/main.c
    src/handle_client.c
    src/network.c
    src/sig_utils.c
)


add_executable(websever ${SOURCES})


target_include_directories(websever PRIVATE ${CMAKE_SOURCE_DIR}/include)
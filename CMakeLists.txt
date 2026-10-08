# 1. Specify minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# 2. Set the project name, version, and language
project(WebServer VERSION 1.0 LANGUAGES C)

# 3. Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")

set(SOURCES
    src/main.c
)


# 4. Define an executable target: executable_name source_files...
add_executable(websever ${SOURCES})


target_include_directories(websever PRIVATE ${CMAKE_SOURCE_DIR}/include)
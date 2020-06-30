cmake_minimum_required(VERSION 3.5)
project(tape)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17")

find_package(Threads)

add_subdirectory(lib/rtaudio)
include_directories(lib/rtaudio)
include_directories(lib/rtaudio/include)

# My Include Dir
include_directories(include)

# Compile a target using NanoGUI
add_executable(tape main.cpp) # ${Resources})

target_link_libraries(tape rtaudio)
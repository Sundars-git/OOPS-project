cmake_minimum_required(VERSION 3.10)
project(pokemon_battle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Single source file — all logic is in headers
add_executable(pokemon_battle main.cpp)

# Include project root for header resolution
target_include_directories(pokemon_battle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

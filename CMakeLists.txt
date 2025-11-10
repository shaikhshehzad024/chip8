cmake_minimum_required(VERSION 3.20)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

file(GLOB SRC_FILES src/*.cpp)
add_executable(Chip8 ${SRC_FILES})

target_link_libraries(Chip8 ${SDL2_LIBRARIES})
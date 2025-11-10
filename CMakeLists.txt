cmake_minimum_required(VERSION 3.20)
project(Chip8)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(Chip8 ${SRC_FILES})
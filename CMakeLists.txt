cmake_minimum_required(VERSION 3.10)
project(CHIP-8)

set(CMAKE_CXX_STANDARD 17)

# Add library
include_directories(include)

# Source files
file(GLOB SRC_FILES src/*.cpp)
# Output binary
add_executable(${PROJECT_NAME} ${SRC_FILES})

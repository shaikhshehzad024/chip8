cmake_minimum_required(VERSION 3.10)
project(CHIP-8)

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Include directories
include_directories(include)

# Output binary
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY bin
    ARCHIVE_OUTPUT_DIRECTORY lib
    LIBRARY_OUTPUT_DIRECTORY lib
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

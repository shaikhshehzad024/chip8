cmake_minimum_required(VERSION 3.20)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

file(GLOB SRC_FILES src/*.cpp)
add_executable(Chip8 ${SRC_FILES})

target_link_libraries(Chip8 ${SDL2_LIBRARIES})

# Optional tests (basic smoke/integration test using CTest)
option(BUILD_TESTS "Build and run tests" OFF)
if(BUILD_TESTS)
	enable_testing()
	# Add a simple CTest that runs the built Chip8 executable and checks for expected output
	add_test(NAME chip8_smoke COMMAND Chip8)
	set_tests_properties(chip8_smoke PROPERTIES PASS_REGULAR_EXPRESSION "memory cleared successfully")
endif()
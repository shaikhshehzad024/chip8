# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /data/data/com.termux/files/usr/bin/sh

# The CMake executable.
CMAKE_COMMAND = /data/data/com.termux/files/usr/bin/cmake

# The command to remove a file.
RM = /data/data/com.termux/files/usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/data/data/com.termux/files/home/dev/CHIP 8"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/data/data/com.termux/files/home/dev/CHIP 8/build"

# Include any dependencies generated for this target.
include CMakeFiles/CHIP-8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CHIP-8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CHIP-8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CHIP-8.dir/flags.make

CMakeFiles/CHIP-8.dir/codegen:
.PHONY : CMakeFiles/CHIP-8.dir/codegen

CMakeFiles/CHIP-8.dir/src/core.cpp.o: CMakeFiles/CHIP-8.dir/flags.make
CMakeFiles/CHIP-8.dir/src/core.cpp.o: /data/data/com.termux/files/home/dev/CHIP\ 8/src/core.cpp
CMakeFiles/CHIP-8.dir/src/core.cpp.o: CMakeFiles/CHIP-8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/data/data/com.termux/files/home/dev/CHIP 8/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CHIP-8.dir/src/core.cpp.o"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CHIP-8.dir/src/core.cpp.o -MF CMakeFiles/CHIP-8.dir/src/core.cpp.o.d -o CMakeFiles/CHIP-8.dir/src/core.cpp.o -c "/data/data/com.termux/files/home/dev/CHIP 8/src/core.cpp"

CMakeFiles/CHIP-8.dir/src/core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CHIP-8.dir/src/core.cpp.i"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/data/data/com.termux/files/home/dev/CHIP 8/src/core.cpp" > CMakeFiles/CHIP-8.dir/src/core.cpp.i

CMakeFiles/CHIP-8.dir/src/core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CHIP-8.dir/src/core.cpp.s"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/data/data/com.termux/files/home/dev/CHIP 8/src/core.cpp" -o CMakeFiles/CHIP-8.dir/src/core.cpp.s

CMakeFiles/CHIP-8.dir/src/getfont.cpp.o: CMakeFiles/CHIP-8.dir/flags.make
CMakeFiles/CHIP-8.dir/src/getfont.cpp.o: /data/data/com.termux/files/home/dev/CHIP\ 8/src/getfont.cpp
CMakeFiles/CHIP-8.dir/src/getfont.cpp.o: CMakeFiles/CHIP-8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/data/data/com.termux/files/home/dev/CHIP 8/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CHIP-8.dir/src/getfont.cpp.o"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CHIP-8.dir/src/getfont.cpp.o -MF CMakeFiles/CHIP-8.dir/src/getfont.cpp.o.d -o CMakeFiles/CHIP-8.dir/src/getfont.cpp.o -c "/data/data/com.termux/files/home/dev/CHIP 8/src/getfont.cpp"

CMakeFiles/CHIP-8.dir/src/getfont.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CHIP-8.dir/src/getfont.cpp.i"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/data/data/com.termux/files/home/dev/CHIP 8/src/getfont.cpp" > CMakeFiles/CHIP-8.dir/src/getfont.cpp.i

CMakeFiles/CHIP-8.dir/src/getfont.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CHIP-8.dir/src/getfont.cpp.s"
	/data/data/com.termux/files/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/data/data/com.termux/files/home/dev/CHIP 8/src/getfont.cpp" -o CMakeFiles/CHIP-8.dir/src/getfont.cpp.s

# Object files for target CHIP-8
CHIP__8_OBJECTS = \
"CMakeFiles/CHIP-8.dir/src/core.cpp.o" \
"CMakeFiles/CHIP-8.dir/src/getfont.cpp.o"

# External object files for target CHIP-8
CHIP__8_EXTERNAL_OBJECTS =

bin/CHIP-8: CMakeFiles/CHIP-8.dir/src/core.cpp.o
bin/CHIP-8: CMakeFiles/CHIP-8.dir/src/getfont.cpp.o
bin/CHIP-8: CMakeFiles/CHIP-8.dir/build.make
bin/CHIP-8: CMakeFiles/CHIP-8.dir/compiler_depend.ts
bin/CHIP-8: CMakeFiles/CHIP-8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/data/data/com.termux/files/home/dev/CHIP 8/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/CHIP-8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CHIP-8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CHIP-8.dir/build: bin/CHIP-8
.PHONY : CMakeFiles/CHIP-8.dir/build

CMakeFiles/CHIP-8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CHIP-8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CHIP-8.dir/clean

CMakeFiles/CHIP-8.dir/depend:
	cd "/data/data/com.termux/files/home/dev/CHIP 8/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/data/data/com.termux/files/home/dev/CHIP 8" "/data/data/com.termux/files/home/dev/CHIP 8" "/data/data/com.termux/files/home/dev/CHIP 8/build" "/data/data/com.termux/files/home/dev/CHIP 8/build" "/data/data/com.termux/files/home/dev/CHIP 8/build/CMakeFiles/CHIP-8.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/CHIP-8.dir/depend


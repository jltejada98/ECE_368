# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/PA3_Revised.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PA3_Revised.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA3_Revised.dir/flags.make

CMakeFiles/PA3_Revised.dir/pa3.c.o: CMakeFiles/PA3_Revised.dir/flags.make
CMakeFiles/PA3_Revised.dir/pa3.c.o: ../pa3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PA3_Revised.dir/pa3.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PA3_Revised.dir/pa3.c.o   -c "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/pa3.c"

CMakeFiles/PA3_Revised.dir/pa3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PA3_Revised.dir/pa3.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/pa3.c" > CMakeFiles/PA3_Revised.dir/pa3.c.i

CMakeFiles/PA3_Revised.dir/pa3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PA3_Revised.dir/pa3.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/pa3.c" -o CMakeFiles/PA3_Revised.dir/pa3.c.s

CMakeFiles/PA3_Revised.dir/node.c.o: CMakeFiles/PA3_Revised.dir/flags.make
CMakeFiles/PA3_Revised.dir/node.c.o: ../node.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PA3_Revised.dir/node.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PA3_Revised.dir/node.c.o   -c "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/node.c"

CMakeFiles/PA3_Revised.dir/node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PA3_Revised.dir/node.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/node.c" > CMakeFiles/PA3_Revised.dir/node.c.i

CMakeFiles/PA3_Revised.dir/node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PA3_Revised.dir/node.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/node.c" -o CMakeFiles/PA3_Revised.dir/node.c.s

CMakeFiles/PA3_Revised.dir/delay.c.o: CMakeFiles/PA3_Revised.dir/flags.make
CMakeFiles/PA3_Revised.dir/delay.c.o: ../delay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/PA3_Revised.dir/delay.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PA3_Revised.dir/delay.c.o   -c "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/delay.c"

CMakeFiles/PA3_Revised.dir/delay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PA3_Revised.dir/delay.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/delay.c" > CMakeFiles/PA3_Revised.dir/delay.c.i

CMakeFiles/PA3_Revised.dir/delay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PA3_Revised.dir/delay.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/delay.c" -o CMakeFiles/PA3_Revised.dir/delay.c.s

# Object files for target PA3_Revised
PA3_Revised_OBJECTS = \
"CMakeFiles/PA3_Revised.dir/pa3.c.o" \
"CMakeFiles/PA3_Revised.dir/node.c.o" \
"CMakeFiles/PA3_Revised.dir/delay.c.o"

# External object files for target PA3_Revised
PA3_Revised_EXTERNAL_OBJECTS =

PA3_Revised: CMakeFiles/PA3_Revised.dir/pa3.c.o
PA3_Revised: CMakeFiles/PA3_Revised.dir/node.c.o
PA3_Revised: CMakeFiles/PA3_Revised.dir/delay.c.o
PA3_Revised: CMakeFiles/PA3_Revised.dir/build.make
PA3_Revised: CMakeFiles/PA3_Revised.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable PA3_Revised"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA3_Revised.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA3_Revised.dir/build: PA3_Revised

.PHONY : CMakeFiles/PA3_Revised.dir/build

CMakeFiles/PA3_Revised.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA3_Revised.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA3_Revised.dir/clean

CMakeFiles/PA3_Revised.dir/depend:
	cd "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised" "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised" "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug" "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug" "/Users/joseluistejada/Documents/Purdue/Year 2/Semester 2/Computer Engineering 368/ECE_368/PA3-Revised/cmake-build-debug/CMakeFiles/PA3_Revised.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PA3_Revised.dir/depend


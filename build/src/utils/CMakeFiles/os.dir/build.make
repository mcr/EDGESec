# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexandru/Projects/EDGESec

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandru/Projects/EDGESec/build

# Include any dependencies generated for this target.
include src/utils/CMakeFiles/os.dir/depend.make

# Include the progress variables for this target.
include src/utils/CMakeFiles/os.dir/progress.make

# Include the compile flags for this target's objects.
include src/utils/CMakeFiles/os.dir/flags.make

src/utils/CMakeFiles/os.dir/os.c.o: src/utils/CMakeFiles/os.dir/flags.make
src/utils/CMakeFiles/os.dir/os.c.o: ../src/utils/os.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/utils/CMakeFiles/os.dir/os.c.o"
	cd /home/alexandru/Projects/EDGESec/build/src/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/os.dir/os.c.o   -c /home/alexandru/Projects/EDGESec/src/utils/os.c

src/utils/CMakeFiles/os.dir/os.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/os.dir/os.c.i"
	cd /home/alexandru/Projects/EDGESec/build/src/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alexandru/Projects/EDGESec/src/utils/os.c > CMakeFiles/os.dir/os.c.i

src/utils/CMakeFiles/os.dir/os.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/os.dir/os.c.s"
	cd /home/alexandru/Projects/EDGESec/build/src/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alexandru/Projects/EDGESec/src/utils/os.c -o CMakeFiles/os.dir/os.c.s

# Object files for target os
os_OBJECTS = \
"CMakeFiles/os.dir/os.c.o"

# External object files for target os
os_EXTERNAL_OBJECTS =

src/utils/libos.a: src/utils/CMakeFiles/os.dir/os.c.o
src/utils/libos.a: src/utils/CMakeFiles/os.dir/build.make
src/utils/libos.a: src/utils/CMakeFiles/os.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libos.a"
	cd /home/alexandru/Projects/EDGESec/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/os.dir/cmake_clean_target.cmake
	cd /home/alexandru/Projects/EDGESec/build/src/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/os.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/utils/CMakeFiles/os.dir/build: src/utils/libos.a

.PHONY : src/utils/CMakeFiles/os.dir/build

src/utils/CMakeFiles/os.dir/clean:
	cd /home/alexandru/Projects/EDGESec/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/os.dir/cmake_clean.cmake
.PHONY : src/utils/CMakeFiles/os.dir/clean

src/utils/CMakeFiles/os.dir/depend:
	cd /home/alexandru/Projects/EDGESec/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandru/Projects/EDGESec /home/alexandru/Projects/EDGESec/src/utils /home/alexandru/Projects/EDGESec/build /home/alexandru/Projects/EDGESec/build/src/utils /home/alexandru/Projects/EDGESec/build/src/utils/CMakeFiles/os.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/utils/CMakeFiles/os.dir/depend


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
include src/radius/CMakeFiles/radius.dir/depend.make

# Include the progress variables for this target.
include src/radius/CMakeFiles/radius.dir/progress.make

# Include the compile flags for this target's objects.
include src/radius/CMakeFiles/radius.dir/flags.make

src/radius/CMakeFiles/radius.dir/radius.c.o: src/radius/CMakeFiles/radius.dir/flags.make
src/radius/CMakeFiles/radius.dir/radius.c.o: ../src/radius/radius.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/radius/CMakeFiles/radius.dir/radius.c.o"
	cd /home/alexandru/Projects/EDGESec/build/src/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/radius.dir/radius.c.o   -c /home/alexandru/Projects/EDGESec/src/radius/radius.c

src/radius/CMakeFiles/radius.dir/radius.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/radius.dir/radius.c.i"
	cd /home/alexandru/Projects/EDGESec/build/src/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alexandru/Projects/EDGESec/src/radius/radius.c > CMakeFiles/radius.dir/radius.c.i

src/radius/CMakeFiles/radius.dir/radius.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/radius.dir/radius.c.s"
	cd /home/alexandru/Projects/EDGESec/build/src/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alexandru/Projects/EDGESec/src/radius/radius.c -o CMakeFiles/radius.dir/radius.c.s

# Object files for target radius
radius_OBJECTS = \
"CMakeFiles/radius.dir/radius.c.o"

# External object files for target radius
radius_EXTERNAL_OBJECTS =

src/radius/libradius.a: src/radius/CMakeFiles/radius.dir/radius.c.o
src/radius/libradius.a: src/radius/CMakeFiles/radius.dir/build.make
src/radius/libradius.a: src/radius/CMakeFiles/radius.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libradius.a"
	cd /home/alexandru/Projects/EDGESec/build/src/radius && $(CMAKE_COMMAND) -P CMakeFiles/radius.dir/cmake_clean_target.cmake
	cd /home/alexandru/Projects/EDGESec/build/src/radius && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/radius.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/radius/CMakeFiles/radius.dir/build: src/radius/libradius.a

.PHONY : src/radius/CMakeFiles/radius.dir/build

src/radius/CMakeFiles/radius.dir/clean:
	cd /home/alexandru/Projects/EDGESec/build/src/radius && $(CMAKE_COMMAND) -P CMakeFiles/radius.dir/cmake_clean.cmake
.PHONY : src/radius/CMakeFiles/radius.dir/clean

src/radius/CMakeFiles/radius.dir/depend:
	cd /home/alexandru/Projects/EDGESec/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandru/Projects/EDGESec /home/alexandru/Projects/EDGESec/src/radius /home/alexandru/Projects/EDGESec/build /home/alexandru/Projects/EDGESec/build/src/radius /home/alexandru/Projects/EDGESec/build/src/radius/CMakeFiles/radius.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/radius/CMakeFiles/radius.dir/depend


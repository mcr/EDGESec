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
include tests/radius/CMakeFiles/ip_addr.dir/depend.make

# Include the progress variables for this target.
include tests/radius/CMakeFiles/ip_addr.dir/progress.make

# Include the compile flags for this target's objects.
include tests/radius/CMakeFiles/ip_addr.dir/flags.make

tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.o: tests/radius/CMakeFiles/ip_addr.dir/flags.make
tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.o: ../tests/radius/ip_addr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.o"
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ip_addr.dir/ip_addr.c.o   -c /home/alexandru/Projects/EDGESec/tests/radius/ip_addr.c

tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ip_addr.dir/ip_addr.c.i"
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alexandru/Projects/EDGESec/tests/radius/ip_addr.c > CMakeFiles/ip_addr.dir/ip_addr.c.i

tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ip_addr.dir/ip_addr.c.s"
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alexandru/Projects/EDGESec/tests/radius/ip_addr.c -o CMakeFiles/ip_addr.dir/ip_addr.c.s

# Object files for target ip_addr
ip_addr_OBJECTS = \
"CMakeFiles/ip_addr.dir/ip_addr.c.o"

# External object files for target ip_addr
ip_addr_EXTERNAL_OBJECTS =

tests/radius/libip_addr.a: tests/radius/CMakeFiles/ip_addr.dir/ip_addr.c.o
tests/radius/libip_addr.a: tests/radius/CMakeFiles/ip_addr.dir/build.make
tests/radius/libip_addr.a: tests/radius/CMakeFiles/ip_addr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandru/Projects/EDGESec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libip_addr.a"
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && $(CMAKE_COMMAND) -P CMakeFiles/ip_addr.dir/cmake_clean_target.cmake
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ip_addr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/radius/CMakeFiles/ip_addr.dir/build: tests/radius/libip_addr.a

.PHONY : tests/radius/CMakeFiles/ip_addr.dir/build

tests/radius/CMakeFiles/ip_addr.dir/clean:
	cd /home/alexandru/Projects/EDGESec/build/tests/radius && $(CMAKE_COMMAND) -P CMakeFiles/ip_addr.dir/cmake_clean.cmake
.PHONY : tests/radius/CMakeFiles/ip_addr.dir/clean

tests/radius/CMakeFiles/ip_addr.dir/depend:
	cd /home/alexandru/Projects/EDGESec/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandru/Projects/EDGESec /home/alexandru/Projects/EDGESec/tests/radius /home/alexandru/Projects/EDGESec/build /home/alexandru/Projects/EDGESec/build/tests/radius /home/alexandru/Projects/EDGESec/build/tests/radius/CMakeFiles/ip_addr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/radius/CMakeFiles/ip_addr.dir/depend


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
CMAKE_SOURCE_DIR = /home/alex/Projects/EDGESec/lib/libnetlink

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Projects/EDGESec/lib/libnetlink/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/libnetlink.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/libnetlink.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/libnetlink.dir/flags.make

lib/CMakeFiles/libnetlink.dir/libnetlink.c.o: lib/CMakeFiles/libnetlink.dir/flags.make
lib/CMakeFiles/libnetlink.dir/libnetlink.c.o: ../lib/libnetlink.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/EDGESec/lib/libnetlink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/libnetlink.dir/libnetlink.c.o"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libnetlink.dir/libnetlink.c.o   -c /home/alex/Projects/EDGESec/lib/libnetlink/lib/libnetlink.c

lib/CMakeFiles/libnetlink.dir/libnetlink.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libnetlink.dir/libnetlink.c.i"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/EDGESec/lib/libnetlink/lib/libnetlink.c > CMakeFiles/libnetlink.dir/libnetlink.c.i

lib/CMakeFiles/libnetlink.dir/libnetlink.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libnetlink.dir/libnetlink.c.s"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/EDGESec/lib/libnetlink/lib/libnetlink.c -o CMakeFiles/libnetlink.dir/libnetlink.c.s

# Object files for target libnetlink
libnetlink_OBJECTS = \
"CMakeFiles/libnetlink.dir/libnetlink.c.o"

# External object files for target libnetlink
libnetlink_EXTERNAL_OBJECTS =

lib/liblibnetlink.so: lib/CMakeFiles/libnetlink.dir/libnetlink.c.o
lib/liblibnetlink.so: lib/CMakeFiles/libnetlink.dir/build.make
lib/liblibnetlink.so: /home/alex/Projects/EDGESec/lib/libmnl-1.0.4/build/lib/libmnl.so
lib/liblibnetlink.so: lib/CMakeFiles/libnetlink.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Projects/EDGESec/lib/libnetlink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library liblibnetlink.so"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libnetlink.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/libnetlink.dir/build: lib/liblibnetlink.so

.PHONY : lib/CMakeFiles/libnetlink.dir/build

lib/CMakeFiles/libnetlink.dir/clean:
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/libnetlink.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/libnetlink.dir/clean

lib/CMakeFiles/libnetlink.dir/depend:
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Projects/EDGESec/lib/libnetlink /home/alex/Projects/EDGESec/lib/libnetlink/lib /home/alex/Projects/EDGESec/lib/libnetlink/build /home/alex/Projects/EDGESec/lib/libnetlink/build/lib /home/alex/Projects/EDGESec/lib/libnetlink/build/lib/CMakeFiles/libnetlink.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/libnetlink.dir/depend


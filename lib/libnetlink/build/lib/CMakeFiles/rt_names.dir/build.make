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
include lib/CMakeFiles/rt_names.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/rt_names.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/rt_names.dir/flags.make

lib/CMakeFiles/rt_names.dir/rt_names.c.o: lib/CMakeFiles/rt_names.dir/flags.make
lib/CMakeFiles/rt_names.dir/rt_names.c.o: ../lib/rt_names.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/EDGESec/lib/libnetlink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/rt_names.dir/rt_names.c.o"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rt_names.dir/rt_names.c.o   -c /home/alex/Projects/EDGESec/lib/libnetlink/lib/rt_names.c

lib/CMakeFiles/rt_names.dir/rt_names.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rt_names.dir/rt_names.c.i"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/EDGESec/lib/libnetlink/lib/rt_names.c > CMakeFiles/rt_names.dir/rt_names.c.i

lib/CMakeFiles/rt_names.dir/rt_names.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rt_names.dir/rt_names.c.s"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/EDGESec/lib/libnetlink/lib/rt_names.c -o CMakeFiles/rt_names.dir/rt_names.c.s

# Object files for target rt_names
rt_names_OBJECTS = \
"CMakeFiles/rt_names.dir/rt_names.c.o"

# External object files for target rt_names
rt_names_EXTERNAL_OBJECTS =

lib/librt_names.so: lib/CMakeFiles/rt_names.dir/rt_names.c.o
lib/librt_names.so: lib/CMakeFiles/rt_names.dir/build.make
lib/librt_names.so: lib/libutils.so
lib/librt_names.so: lib/libjson_print.a
lib/librt_names.so: lib/libjson_writer.a
lib/librt_names.so: lib/libcolor.a
lib/librt_names.so: lib/libmpls_ntop.a
lib/librt_names.so: lib/libll_addr.a
lib/librt_names.so: lib/libmpls_pton.a
lib/librt_names.so: lib/CMakeFiles/rt_names.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Projects/EDGESec/lib/libnetlink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library librt_names.so"
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rt_names.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/rt_names.dir/build: lib/librt_names.so

.PHONY : lib/CMakeFiles/rt_names.dir/build

lib/CMakeFiles/rt_names.dir/clean:
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/rt_names.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/rt_names.dir/clean

lib/CMakeFiles/rt_names.dir/depend:
	cd /home/alex/Projects/EDGESec/lib/libnetlink/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Projects/EDGESec/lib/libnetlink /home/alex/Projects/EDGESec/lib/libnetlink/lib /home/alex/Projects/EDGESec/lib/libnetlink/build /home/alex/Projects/EDGESec/lib/libnetlink/build/lib /home/alex/Projects/EDGESec/lib/libnetlink/build/lib/CMakeFiles/rt_names.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/rt_names.dir/depend


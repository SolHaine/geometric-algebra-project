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
CMAKE_SOURCE_DIR = /home/solene/Documents/garamon_c3ga

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/solene/Documents/garamon_c3ga/build

# Utility rule file for html.

# Include the progress variables for this target.
include doc/CMakeFiles/html.dir/progress.make

doc/CMakeFiles/html:
	cd /home/solene/Documents/garamon_c3ga/build/doc && /usr/bin/doxygen /home/solene/Documents/garamon_c3ga/build/doc/Doxyfile-html

html: doc/CMakeFiles/html
html: doc/CMakeFiles/html.dir/build.make

.PHONY : html

# Rule to build all files generated by this target.
doc/CMakeFiles/html.dir/build: html

.PHONY : doc/CMakeFiles/html.dir/build

doc/CMakeFiles/html.dir/clean:
	cd /home/solene/Documents/garamon_c3ga/build/doc && $(CMAKE_COMMAND) -P CMakeFiles/html.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/html.dir/clean

doc/CMakeFiles/html.dir/depend:
	cd /home/solene/Documents/garamon_c3ga/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/solene/Documents/garamon_c3ga /home/solene/Documents/garamon_c3ga/doc /home/solene/Documents/garamon_c3ga/build /home/solene/Documents/garamon_c3ga/build/doc /home/solene/Documents/garamon_c3ga/build/doc/CMakeFiles/html.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/html.dir/depend


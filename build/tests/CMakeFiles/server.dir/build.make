# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/user/Desktop/ndsl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/ndsl/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/server.dir/flags.make

tests/CMakeFiles/server.dir/ping-pong/server.cc.o: tests/CMakeFiles/server.dir/flags.make
tests/CMakeFiles/server.dir/ping-pong/server.cc.o: ../tests/ping-pong/server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/server.dir/ping-pong/server.cc.o"
	cd /home/user/Desktop/ndsl/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/ping-pong/server.cc.o -c /home/user/Desktop/ndsl/tests/ping-pong/server.cc

tests/CMakeFiles/server.dir/ping-pong/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/ping-pong/server.cc.i"
	cd /home/user/Desktop/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/tests/ping-pong/server.cc > CMakeFiles/server.dir/ping-pong/server.cc.i

tests/CMakeFiles/server.dir/ping-pong/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/ping-pong/server.cc.s"
	cd /home/user/Desktop/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/tests/ping-pong/server.cc -o CMakeFiles/server.dir/ping-pong/server.cc.s

tests/CMakeFiles/server.dir/ping-pong/server.cc.o.requires:

.PHONY : tests/CMakeFiles/server.dir/ping-pong/server.cc.o.requires

tests/CMakeFiles/server.dir/ping-pong/server.cc.o.provides: tests/CMakeFiles/server.dir/ping-pong/server.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/server.dir/build.make tests/CMakeFiles/server.dir/ping-pong/server.cc.o.provides.build
.PHONY : tests/CMakeFiles/server.dir/ping-pong/server.cc.o.provides

tests/CMakeFiles/server.dir/ping-pong/server.cc.o.provides.build: tests/CMakeFiles/server.dir/ping-pong/server.cc.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/ping-pong/server.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

bin/server: tests/CMakeFiles/server.dir/ping-pong/server.cc.o
bin/server: tests/CMakeFiles/server.dir/build.make
bin/server: bin/libndsl.a
bin/server: bin/libplugin.so
bin/server: tests/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/server"
	cd /home/user/Desktop/ndsl/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/server.dir/build: bin/server

.PHONY : tests/CMakeFiles/server.dir/build

tests/CMakeFiles/server.dir/requires: tests/CMakeFiles/server.dir/ping-pong/server.cc.o.requires

.PHONY : tests/CMakeFiles/server.dir/requires

tests/CMakeFiles/server.dir/clean:
	cd /home/user/Desktop/ndsl/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/server.dir/clean

tests/CMakeFiles/server.dir/depend:
	cd /home/user/Desktop/ndsl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Desktop/ndsl /home/user/Desktop/ndsl/tests /home/user/Desktop/ndsl/build /home/user/Desktop/ndsl/build/tests /home/user/Desktop/ndsl/build/tests/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/server.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/felipetrost/.local/lib/python3.12/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/felipetrost/.local/lib/python3.12/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/felipetrost/projects/personal/remote-rgb-lights/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/felipetrost/projects/personal/remote-rgb-lights/testbuild

# Include any dependencies generated for this target.
include CMakeFiles/patterns_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/patterns_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/patterns_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/patterns_test.dir/flags.make

CMakeFiles/patterns_test.dir/patterns_test.cpp.o: CMakeFiles/patterns_test.dir/flags.make
CMakeFiles/patterns_test.dir/patterns_test.cpp.o: /home/felipetrost/projects/personal/remote-rgb-lights/tests/patterns_test.cpp
CMakeFiles/patterns_test.dir/patterns_test.cpp.o: CMakeFiles/patterns_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/felipetrost/projects/personal/remote-rgb-lights/testbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/patterns_test.dir/patterns_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/patterns_test.dir/patterns_test.cpp.o -MF CMakeFiles/patterns_test.dir/patterns_test.cpp.o.d -o CMakeFiles/patterns_test.dir/patterns_test.cpp.o -c /home/felipetrost/projects/personal/remote-rgb-lights/tests/patterns_test.cpp

CMakeFiles/patterns_test.dir/patterns_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/patterns_test.dir/patterns_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felipetrost/projects/personal/remote-rgb-lights/tests/patterns_test.cpp > CMakeFiles/patterns_test.dir/patterns_test.cpp.i

CMakeFiles/patterns_test.dir/patterns_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/patterns_test.dir/patterns_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felipetrost/projects/personal/remote-rgb-lights/tests/patterns_test.cpp -o CMakeFiles/patterns_test.dir/patterns_test.cpp.s

# Object files for target patterns_test
patterns_test_OBJECTS = \
"CMakeFiles/patterns_test.dir/patterns_test.cpp.o"

# External object files for target patterns_test
patterns_test_EXTERNAL_OBJECTS =

patterns_test: CMakeFiles/patterns_test.dir/patterns_test.cpp.o
patterns_test: CMakeFiles/patterns_test.dir/build.make
patterns_test: lib/libgtest_main.a
patterns_test: lib/libgtest.a
patterns_test: CMakeFiles/patterns_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/felipetrost/projects/personal/remote-rgb-lights/testbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable patterns_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/patterns_test.dir/link.txt --verbose=$(VERBOSE)
	/home/felipetrost/.local/lib/python3.12/site-packages/cmake/data/bin/cmake -D TEST_TARGET=patterns_test -D TEST_EXECUTABLE=/home/felipetrost/projects/personal/remote-rgb-lights/testbuild/patterns_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/felipetrost/projects/personal/remote-rgb-lights/testbuild -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=patterns_test_TESTS -D CTEST_FILE=/home/felipetrost/projects/personal/remote-rgb-lights/testbuild/patterns_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /home/felipetrost/.local/lib/python3.12/site-packages/cmake/data/share/cmake-3.29/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/patterns_test.dir/build: patterns_test
.PHONY : CMakeFiles/patterns_test.dir/build

CMakeFiles/patterns_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/patterns_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/patterns_test.dir/clean

CMakeFiles/patterns_test.dir/depend:
	cd /home/felipetrost/projects/personal/remote-rgb-lights/testbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/felipetrost/projects/personal/remote-rgb-lights/tests /home/felipetrost/projects/personal/remote-rgb-lights/tests /home/felipetrost/projects/personal/remote-rgb-lights/testbuild /home/felipetrost/projects/personal/remote-rgb-lights/testbuild /home/felipetrost/projects/personal/remote-rgb-lights/testbuild/CMakeFiles/patterns_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/patterns_test.dir/depend


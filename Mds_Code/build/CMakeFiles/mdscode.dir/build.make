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
CMAKE_SOURCE_DIR = /home/madophs/Documents/git/Mds-Code/Mds_Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/madophs/Documents/git/Mds-Code/Mds_Code/build

# Include any dependencies generated for this target.
include CMakeFiles/mdscode.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mdscode.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mdscode.dir/flags.make

CMakeFiles/mdscode.dir/mdscode.cpp.o: CMakeFiles/mdscode.dir/flags.make
CMakeFiles/mdscode.dir/mdscode.cpp.o: ../mdscode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/madophs/Documents/git/Mds-Code/Mds_Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mdscode.dir/mdscode.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mdscode.dir/mdscode.cpp.o -c /home/madophs/Documents/git/Mds-Code/Mds_Code/mdscode.cpp

CMakeFiles/mdscode.dir/mdscode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mdscode.dir/mdscode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/madophs/Documents/git/Mds-Code/Mds_Code/mdscode.cpp > CMakeFiles/mdscode.dir/mdscode.cpp.i

CMakeFiles/mdscode.dir/mdscode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mdscode.dir/mdscode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/madophs/Documents/git/Mds-Code/Mds_Code/mdscode.cpp -o CMakeFiles/mdscode.dir/mdscode.cpp.s

# Object files for target mdscode
mdscode_OBJECTS = \
"CMakeFiles/mdscode.dir/mdscode.cpp.o"

# External object files for target mdscode
mdscode_EXTERNAL_OBJECTS =

mdscode: CMakeFiles/mdscode.dir/mdscode.cpp.o
mdscode: CMakeFiles/mdscode.dir/build.make
mdscode: src/liblibmdscode.a
mdscode: CMakeFiles/mdscode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/madophs/Documents/git/Mds-Code/Mds_Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mdscode"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mdscode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mdscode.dir/build: mdscode

.PHONY : CMakeFiles/mdscode.dir/build

CMakeFiles/mdscode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mdscode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mdscode.dir/clean

CMakeFiles/mdscode.dir/depend:
	cd /home/madophs/Documents/git/Mds-Code/Mds_Code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/madophs/Documents/git/Mds-Code/Mds_Code /home/madophs/Documents/git/Mds-Code/Mds_Code /home/madophs/Documents/git/Mds-Code/Mds_Code/build /home/madophs/Documents/git/Mds-Code/Mds_Code/build /home/madophs/Documents/git/Mds-Code/Mds_Code/build/CMakeFiles/mdscode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mdscode.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/supdan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6262.62/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/supdan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6262.62/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/supdan/code/UINS_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/supdan/code/UINS_ws/src/cmake-build-debug

# Include any dependencies generated for this target.
include crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/depend.make

# Include the progress variables for this target.
include crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/progress.make

# Include the compile flags for this target's objects.
include crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/flags.make

crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.o: crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/flags.make
crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.o: ../crazyflie_ros/crazyflie_tools/src/version.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/supdan/code/UINS_ws/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.o"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/version.dir/src/version.cpp.o -c /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_tools/src/version.cpp

crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version.dir/src/version.cpp.i"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_tools/src/version.cpp > CMakeFiles/version.dir/src/version.cpp.i

crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version.dir/src/version.cpp.s"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_tools/src/version.cpp -o CMakeFiles/version.dir/src/version.cpp.s

# Object files for target version
version_OBJECTS = \
"CMakeFiles/version.dir/src/version.cpp.o"

# External object files for target version
version_EXTERNAL_OBJECTS =

/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/src/version.cpp.o
/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/build.make
/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: /home/supdan/code/UINS_ws/devel/lib/libcrazyflie_cpp.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version: crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/supdan/code/UINS_ws/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/version.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/build: /home/supdan/code/UINS_ws/devel/lib/crazyflie_tools/version

.PHONY : crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/build

crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/clean:
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools && $(CMAKE_COMMAND) -P CMakeFiles/version.dir/cmake_clean.cmake
.PHONY : crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/clean

crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/depend:
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/supdan/code/UINS_ws/src /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_tools /home/supdan/code/UINS_ws/src/cmake-build-debug /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : crazyflie_ros/crazyflie_tools/CMakeFiles/version.dir/depend


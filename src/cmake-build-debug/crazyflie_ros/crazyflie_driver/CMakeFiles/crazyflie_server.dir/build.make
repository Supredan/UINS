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
include crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/depend.make

# Include the progress variables for this target.
include crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/progress.make

# Include the compile flags for this target's objects.
include crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/flags.make

crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o: crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/flags.make
crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o: ../crazyflie_ros/crazyflie_driver/src/crazyflie_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/supdan/code/UINS_ws/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o -c /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_driver/src/crazyflie_server.cpp

crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.i"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_driver/src/crazyflie_server.cpp > CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.i

crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.s"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_driver/src/crazyflie_server.cpp -o CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.s

# Object files for target crazyflie_server
crazyflie_server_OBJECTS = \
"CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o"

# External object files for target crazyflie_server
crazyflie_server_EXTERNAL_OBJECTS =

/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/src/crazyflie_server.cpp.o
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/build.make
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libtf.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libtf2_ros.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libactionlib.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libmessage_filters.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libroscpp.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libtf2.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/librosconsole.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/librostime.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /opt/ros/kinetic/lib/libcpp_common.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /home/supdan/code/UINS_ws/devel/lib/libcrazyflie_cpp.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
/home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server: crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/supdan/code/UINS_ws/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server"
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crazyflie_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/build: /home/supdan/code/UINS_ws/devel/lib/crazyflie_driver/crazyflie_server

.PHONY : crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/build

crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/clean:
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver && $(CMAKE_COMMAND) -P CMakeFiles/crazyflie_server.dir/cmake_clean.cmake
.PHONY : crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/clean

crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/depend:
	cd /home/supdan/code/UINS_ws/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/supdan/code/UINS_ws/src /home/supdan/code/UINS_ws/src/crazyflie_ros/crazyflie_driver /home/supdan/code/UINS_ws/src/cmake-build-debug /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver /home/supdan/code/UINS_ws/src/cmake-build-debug/crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : crazyflie_ros/crazyflie_driver/CMakeFiles/crazyflie_server.dir/depend


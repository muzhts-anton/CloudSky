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
CMAKE_SOURCE_DIR = /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build

# Include any dependencies generated for this target.
include lib/ServerConnection/CMakeFiles/ServerConnection.dir/depend.make

# Include the progress variables for this target.
include lib/ServerConnection/CMakeFiles/ServerConnection.dir/progress.make

# Include the compile flags for this target's objects.
include lib/ServerConnection/CMakeFiles/ServerConnection.dir/flags.make

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o: lib/ServerConnection/CMakeFiles/ServerConnection.dir/flags.make
lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o: ../lib/ServerConnection/src/TCPServerSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/TCPServerSocket.cpp

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/TCPServerSocket.cpp > CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.i

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/TCPServerSocket.cpp -o CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.s

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o: lib/ServerConnection/CMakeFiles/ServerConnection.dir/flags.make
lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o: ../lib/ServerConnection/src/UDPServerSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/UDPServerSocket.cpp

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/UDPServerSocket.cpp > CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.i

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/UDPServerSocket.cpp -o CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.s

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.o: lib/ServerConnection/CMakeFiles/ServerConnection.dir/flags.make
lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.o: ../lib/ServerConnection/src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerConnection.dir/src/Server.cpp.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Server.cpp

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerConnection.dir/src/Server.cpp.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Server.cpp > CMakeFiles/ServerConnection.dir/src/Server.cpp.i

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerConnection.dir/src/Server.cpp.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Server.cpp -o CMakeFiles/ServerConnection.dir/src/Server.cpp.s

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.o: lib/ServerConnection/CMakeFiles/ServerConnection.dir/flags.make
lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.o: ../lib/ServerConnection/src/Connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerConnection.dir/src/Connection.cpp.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Connection.cpp

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerConnection.dir/src/Connection.cpp.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Connection.cpp > CMakeFiles/ServerConnection.dir/src/Connection.cpp.i

lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerConnection.dir/src/Connection.cpp.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection/src/Connection.cpp -o CMakeFiles/ServerConnection.dir/src/Connection.cpp.s

# Object files for target ServerConnection
ServerConnection_OBJECTS = \
"CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o" \
"CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o" \
"CMakeFiles/ServerConnection.dir/src/Server.cpp.o" \
"CMakeFiles/ServerConnection.dir/src/Connection.cpp.o"

# External object files for target ServerConnection
ServerConnection_EXTERNAL_OBJECTS =

lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/TCPServerSocket.cpp.o
lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/UDPServerSocket.cpp.o
lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Server.cpp.o
lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/src/Connection.cpp.o
lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/build.make
lib/ServerConnection/libServerConnection.a: lib/ServerConnection/CMakeFiles/ServerConnection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libServerConnection.a"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && $(CMAKE_COMMAND) -P CMakeFiles/ServerConnection.dir/cmake_clean_target.cmake
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServerConnection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/ServerConnection/CMakeFiles/ServerConnection.dir/build: lib/ServerConnection/libServerConnection.a

.PHONY : lib/ServerConnection/CMakeFiles/ServerConnection.dir/build

lib/ServerConnection/CMakeFiles/ServerConnection.dir/clean:
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection && $(CMAKE_COMMAND) -P CMakeFiles/ServerConnection.dir/cmake_clean.cmake
.PHONY : lib/ServerConnection/CMakeFiles/ServerConnection.dir/clean

lib/ServerConnection/CMakeFiles/ServerConnection.dir/depend:
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/ServerConnection /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/ServerConnection/CMakeFiles/ServerConnection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/ServerConnection/CMakeFiles/ServerConnection.dir/depend


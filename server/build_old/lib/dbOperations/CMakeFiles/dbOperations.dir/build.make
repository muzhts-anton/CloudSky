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
include lib/dbOperations/CMakeFiles/dbOperations.dir/depend.make

# Include the progress variables for this target.
include lib/dbOperations/CMakeFiles/dbOperations.dir/progress.make

# Include the compile flags for this target's objects.
include lib/dbOperations/CMakeFiles/dbOperations.dir/flags.make

lib/dbOperations/dbMessages.pb.h: ../lib/dbOperations/src/dbMessages.proto
lib/dbOperations/dbMessages.pb.h: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running cpp protocol buffer compiler on src/dbMessages.proto"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/local/bin/protoc --cpp_out /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations -I /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations/src /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations/src/dbMessages.proto

lib/dbOperations/dbMessages.pb.cc: lib/dbOperations/dbMessages.pb.h
	@$(CMAKE_COMMAND) -E touch_nocreate lib/dbOperations/dbMessages.pb.cc

lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o: lib/dbOperations/CMakeFiles/dbOperations.dir/flags.make
lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o: ../lib/dbOperations/src/dbOperations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations/src/dbOperations.cpp

lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dbOperations.dir/src/dbOperations.cpp.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations/src/dbOperations.cpp > CMakeFiles/dbOperations.dir/src/dbOperations.cpp.i

lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dbOperations.dir/src/dbOperations.cpp.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations/src/dbOperations.cpp -o CMakeFiles/dbOperations.dir/src/dbOperations.cpp.s

lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o: lib/dbOperations/CMakeFiles/dbOperations.dir/flags.make
lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o: lib/dbOperations/dbMessages.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o -c /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations/dbMessages.pb.cc

lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dbOperations.dir/dbMessages.pb.cc.i"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations/dbMessages.pb.cc > CMakeFiles/dbOperations.dir/dbMessages.pb.cc.i

lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dbOperations.dir/dbMessages.pb.cc.s"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations/dbMessages.pb.cc -o CMakeFiles/dbOperations.dir/dbMessages.pb.cc.s

# Object files for target dbOperations
dbOperations_OBJECTS = \
"CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o" \
"CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o"

# External object files for target dbOperations
dbOperations_EXTERNAL_OBJECTS =

lib/dbOperations/libdbOperations.a: lib/dbOperations/CMakeFiles/dbOperations.dir/src/dbOperations.cpp.o
lib/dbOperations/libdbOperations.a: lib/dbOperations/CMakeFiles/dbOperations.dir/dbMessages.pb.cc.o
lib/dbOperations/libdbOperations.a: lib/dbOperations/CMakeFiles/dbOperations.dir/build.make
lib/dbOperations/libdbOperations.a: lib/dbOperations/CMakeFiles/dbOperations.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libdbOperations.a"
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && $(CMAKE_COMMAND) -P CMakeFiles/dbOperations.dir/cmake_clean_target.cmake
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbOperations.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/dbOperations/CMakeFiles/dbOperations.dir/build: lib/dbOperations/libdbOperations.a

.PHONY : lib/dbOperations/CMakeFiles/dbOperations.dir/build

lib/dbOperations/CMakeFiles/dbOperations.dir/clean:
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations && $(CMAKE_COMMAND) -P CMakeFiles/dbOperations.dir/cmake_clean.cmake
.PHONY : lib/dbOperations/CMakeFiles/dbOperations.dir/clean

lib/dbOperations/CMakeFiles/dbOperations.dir/depend: lib/dbOperations/dbMessages.pb.h
lib/dbOperations/CMakeFiles/dbOperations.dir/depend: lib/dbOperations/dbMessages.pb.cc
	cd /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/lib/dbOperations /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations /media/paul/kalashkov/university/thirdTerm/vk/cloudSky/server/build/lib/dbOperations/CMakeFiles/dbOperations.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/dbOperations/CMakeFiles/dbOperations.dir/depend


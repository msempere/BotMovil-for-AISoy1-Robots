# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build

# Include any dependencies generated for this target.
include src/CMakeFiles/NRF24L01.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/NRF24L01.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/NRF24L01.dir/flags.make

# Object files for target NRF24L01
NRF24L01_OBJECTS =

# External object files for target NRF24L01
NRF24L01_EXTERNAL_OBJECTS =

src/libNRF24L01.a: src/CMakeFiles/NRF24L01.dir/build.make
src/libNRF24L01.a: src/CMakeFiles/NRF24L01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libNRF24L01.a"
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/NRF24L01.dir/cmake_clean_target.cmake
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NRF24L01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/NRF24L01.dir/build: src/libNRF24L01.a
.PHONY : src/CMakeFiles/NRF24L01.dir/build

src/CMakeFiles/NRF24L01.dir/requires:
.PHONY : src/CMakeFiles/NRF24L01.dir/requires

src/CMakeFiles/NRF24L01.dir/clean:
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/NRF24L01.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/NRF24L01.dir/clean

src/CMakeFiles/NRF24L01.dir/depend:
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/src /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src/CMakeFiles/NRF24L01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/NRF24L01.dir/depend


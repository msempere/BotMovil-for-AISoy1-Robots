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
include src/CMakeFiles/MIRF.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/MIRF.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MIRF.dir/flags.make

src/CMakeFiles/MIRF.dir/mirf.c.o: src/CMakeFiles/MIRF.dir/flags.make
src/CMakeFiles/MIRF.dir/mirf.c.o: ../src/mirf.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/MIRF.dir/mirf.c.o"
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && /home/aisoy-sdk/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/MIRF.dir/mirf.c.o   -c /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/src/mirf.c

src/CMakeFiles/MIRF.dir/mirf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MIRF.dir/mirf.c.i"
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && /home/aisoy-sdk/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/src/mirf.c > CMakeFiles/MIRF.dir/mirf.c.i

src/CMakeFiles/MIRF.dir/mirf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MIRF.dir/mirf.c.s"
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && /home/aisoy-sdk/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/src/mirf.c -o CMakeFiles/MIRF.dir/mirf.c.s

src/CMakeFiles/MIRF.dir/mirf.c.o.requires:
.PHONY : src/CMakeFiles/MIRF.dir/mirf.c.o.requires

src/CMakeFiles/MIRF.dir/mirf.c.o.provides: src/CMakeFiles/MIRF.dir/mirf.c.o.requires
	$(MAKE) -f src/CMakeFiles/MIRF.dir/build.make src/CMakeFiles/MIRF.dir/mirf.c.o.provides.build
.PHONY : src/CMakeFiles/MIRF.dir/mirf.c.o.provides

src/CMakeFiles/MIRF.dir/mirf.c.o.provides.build: src/CMakeFiles/MIRF.dir/mirf.c.o
.PHONY : src/CMakeFiles/MIRF.dir/mirf.c.o.provides.build

# Object files for target MIRF
MIRF_OBJECTS = \
"CMakeFiles/MIRF.dir/mirf.c.o"

# External object files for target MIRF
MIRF_EXTERNAL_OBJECTS =

src/libMIRF.a: src/CMakeFiles/MIRF.dir/mirf.c.o
src/libMIRF.a: src/CMakeFiles/MIRF.dir/build.make
src/libMIRF.a: src/CMakeFiles/MIRF.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libMIRF.a"
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MIRF.dir/cmake_clean_target.cmake
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MIRF.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MIRF.dir/build: src/libMIRF.a
.PHONY : src/CMakeFiles/MIRF.dir/build

src/CMakeFiles/MIRF.dir/requires: src/CMakeFiles/MIRF.dir/mirf.c.o.requires
.PHONY : src/CMakeFiles/MIRF.dir/requires

src/CMakeFiles/MIRF.dir/clean:
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MIRF.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MIRF.dir/clean

src/CMakeFiles/MIRF.dir/depend:
	cd /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/src /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src /home/aisoy-sdk/repo/SDK/apps/msempere/newBotMovil/build/src/CMakeFiles/MIRF.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MIRF.dir/depend


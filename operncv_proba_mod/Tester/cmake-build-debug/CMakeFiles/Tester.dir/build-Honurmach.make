# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Tester.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Tester.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tester.dir/flags.make

CMakeFiles/Tester.dir/main_promtandkey.cpp.obj: CMakeFiles/Tester.dir/flags.make
CMakeFiles/Tester.dir/main_promtandkey.cpp.obj: ../main_promtandkey.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tester.dir/main_promtandkey.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Tester.dir\main_promtandkey.cpp.obj -c "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\main_promtandkey.cpp"

CMakeFiles/Tester.dir/main_promtandkey.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tester.dir/main_promtandkey.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\main_promtandkey.cpp" > CMakeFiles\Tester.dir\main_promtandkey.cpp.i

CMakeFiles/Tester.dir/main_promtandkey.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tester.dir/main_promtandkey.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\main_promtandkey.cpp" -o CMakeFiles\Tester.dir\main_promtandkey.cpp.s

# Object files for target Tester
Tester_OBJECTS = \
"CMakeFiles/Tester.dir/main_promtandkey.cpp.obj"

# External object files for target Tester
Tester_EXTERNAL_OBJECTS =

Tester.exe: CMakeFiles/Tester.dir/main_promtandkey.cpp.obj
Tester.exe: CMakeFiles/Tester.dir/build.make
Tester.exe: CMakeFiles/Tester.dir/linklibs.rsp
Tester.exe: CMakeFiles/Tester.dir/objects1.rsp
Tester.exe: CMakeFiles/Tester.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tester.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Tester.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tester.dir/build: Tester.exe
.PHONY : CMakeFiles/Tester.dir/build

CMakeFiles/Tester.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Tester.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Tester.dir/clean

CMakeFiles/Tester.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester" "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester" "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug" "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug" "C:\Users\ghuno\OneDrive\Documents\Visual Studio 2008\Projects\opencv_proba_mod\Tester\cmake-build-debug\CMakeFiles\Tester.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Tester.dir/depend


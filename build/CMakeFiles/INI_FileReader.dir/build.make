# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Archivio\VS Code\C++\INI_FileReader"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Archivio\VS Code\C++\INI_FileReader\build"

# Include any dependencies generated for this target.
include CMakeFiles/INI_FileReader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/INI_FileReader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/INI_FileReader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/INI_FileReader.dir/flags.make

CMakeFiles/INI_FileReader.dir/main.cpp.obj: CMakeFiles/INI_FileReader.dir/flags.make
CMakeFiles/INI_FileReader.dir/main.cpp.obj: ../main.cpp
CMakeFiles/INI_FileReader.dir/main.cpp.obj: CMakeFiles/INI_FileReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Archivio\VS Code\C++\INI_FileReader\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/INI_FileReader.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/INI_FileReader.dir/main.cpp.obj -MF CMakeFiles\INI_FileReader.dir\main.cpp.obj.d -o CMakeFiles\INI_FileReader.dir\main.cpp.obj -c "E:\Archivio\VS Code\C++\INI_FileReader\main.cpp"

CMakeFiles/INI_FileReader.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/INI_FileReader.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Archivio\VS Code\C++\INI_FileReader\main.cpp" > CMakeFiles\INI_FileReader.dir\main.cpp.i

CMakeFiles/INI_FileReader.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/INI_FileReader.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Archivio\VS Code\C++\INI_FileReader\main.cpp" -o CMakeFiles\INI_FileReader.dir\main.cpp.s

# Object files for target INI_FileReader
INI_FileReader_OBJECTS = \
"CMakeFiles/INI_FileReader.dir/main.cpp.obj"

# External object files for target INI_FileReader
INI_FileReader_EXTERNAL_OBJECTS =

INI_FileReader.exe: CMakeFiles/INI_FileReader.dir/main.cpp.obj
INI_FileReader.exe: CMakeFiles/INI_FileReader.dir/build.make
INI_FileReader.exe: CMakeFiles/INI_FileReader.dir/linklibs.rsp
INI_FileReader.exe: CMakeFiles/INI_FileReader.dir/objects1.rsp
INI_FileReader.exe: CMakeFiles/INI_FileReader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Archivio\VS Code\C++\INI_FileReader\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable INI_FileReader.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\INI_FileReader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/INI_FileReader.dir/build: INI_FileReader.exe
.PHONY : CMakeFiles/INI_FileReader.dir/build

CMakeFiles/INI_FileReader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\INI_FileReader.dir\cmake_clean.cmake
.PHONY : CMakeFiles/INI_FileReader.dir/clean

CMakeFiles/INI_FileReader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Archivio\VS Code\C++\INI_FileReader" "E:\Archivio\VS Code\C++\INI_FileReader" "E:\Archivio\VS Code\C++\INI_FileReader\build" "E:\Archivio\VS Code\C++\INI_FileReader\build" "E:\Archivio\VS Code\C++\INI_FileReader\build\CMakeFiles\INI_FileReader.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/INI_FileReader.dir/depend

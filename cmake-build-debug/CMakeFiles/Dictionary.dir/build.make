# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/adeshchoudhar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7628.27/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/adeshchoudhar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7628.27/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adeshchoudhar/GitHub/Dictionary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Dictionary.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Dictionary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Dictionary.dir/flags.make

CMakeFiles/Dictionary.dir/main.c.o: CMakeFiles/Dictionary.dir/flags.make
CMakeFiles/Dictionary.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Dictionary.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Dictionary.dir/main.c.o -c /home/adeshchoudhar/GitHub/Dictionary/main.c

CMakeFiles/Dictionary.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Dictionary.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adeshchoudhar/GitHub/Dictionary/main.c > CMakeFiles/Dictionary.dir/main.c.i

CMakeFiles/Dictionary.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Dictionary.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adeshchoudhar/GitHub/Dictionary/main.c -o CMakeFiles/Dictionary.dir/main.c.s

CMakeFiles/Dictionary.dir/hash.c.o: CMakeFiles/Dictionary.dir/flags.make
CMakeFiles/Dictionary.dir/hash.c.o: ../hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Dictionary.dir/hash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Dictionary.dir/hash.c.o -c /home/adeshchoudhar/GitHub/Dictionary/hash.c

CMakeFiles/Dictionary.dir/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Dictionary.dir/hash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adeshchoudhar/GitHub/Dictionary/hash.c > CMakeFiles/Dictionary.dir/hash.c.i

CMakeFiles/Dictionary.dir/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Dictionary.dir/hash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adeshchoudhar/GitHub/Dictionary/hash.c -o CMakeFiles/Dictionary.dir/hash.c.s

CMakeFiles/Dictionary.dir/trie.c.o: CMakeFiles/Dictionary.dir/flags.make
CMakeFiles/Dictionary.dir/trie.c.o: ../trie.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Dictionary.dir/trie.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Dictionary.dir/trie.c.o -c /home/adeshchoudhar/GitHub/Dictionary/trie.c

CMakeFiles/Dictionary.dir/trie.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Dictionary.dir/trie.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adeshchoudhar/GitHub/Dictionary/trie.c > CMakeFiles/Dictionary.dir/trie.c.i

CMakeFiles/Dictionary.dir/trie.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Dictionary.dir/trie.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adeshchoudhar/GitHub/Dictionary/trie.c -o CMakeFiles/Dictionary.dir/trie.c.s

CMakeFiles/Dictionary.dir/helpers.c.o: CMakeFiles/Dictionary.dir/flags.make
CMakeFiles/Dictionary.dir/helpers.c.o: ../helpers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Dictionary.dir/helpers.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Dictionary.dir/helpers.c.o -c /home/adeshchoudhar/GitHub/Dictionary/helpers.c

CMakeFiles/Dictionary.dir/helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Dictionary.dir/helpers.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adeshchoudhar/GitHub/Dictionary/helpers.c > CMakeFiles/Dictionary.dir/helpers.c.i

CMakeFiles/Dictionary.dir/helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Dictionary.dir/helpers.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adeshchoudhar/GitHub/Dictionary/helpers.c -o CMakeFiles/Dictionary.dir/helpers.c.s

# Object files for target Dictionary
Dictionary_OBJECTS = \
"CMakeFiles/Dictionary.dir/main.c.o" \
"CMakeFiles/Dictionary.dir/hash.c.o" \
"CMakeFiles/Dictionary.dir/trie.c.o" \
"CMakeFiles/Dictionary.dir/helpers.c.o"

# External object files for target Dictionary
Dictionary_EXTERNAL_OBJECTS =

Dictionary: CMakeFiles/Dictionary.dir/main.c.o
Dictionary: CMakeFiles/Dictionary.dir/hash.c.o
Dictionary: CMakeFiles/Dictionary.dir/trie.c.o
Dictionary: CMakeFiles/Dictionary.dir/helpers.c.o
Dictionary: CMakeFiles/Dictionary.dir/build.make
Dictionary: CMakeFiles/Dictionary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Dictionary"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Dictionary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Dictionary.dir/build: Dictionary

.PHONY : CMakeFiles/Dictionary.dir/build

CMakeFiles/Dictionary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Dictionary.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Dictionary.dir/clean

CMakeFiles/Dictionary.dir/depend:
	cd /home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adeshchoudhar/GitHub/Dictionary /home/adeshchoudhar/GitHub/Dictionary /home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug /home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug /home/adeshchoudhar/GitHub/Dictionary/cmake-build-debug/CMakeFiles/Dictionary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Dictionary.dir/depend


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
CMAKE_SOURCE_DIR = "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram"

# Include any dependencies generated for this target.
include CMakeFiles/histogram.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/histogram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/histogram.dir/flags.make

CMakeFiles/histogram.dir/histogram.cpp.o: CMakeFiles/histogram.dir/flags.make
CMakeFiles/histogram.dir/histogram.cpp.o: histogram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/histogram.dir/histogram.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/histogram.dir/histogram.cpp.o -c "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/histogram.cpp"

CMakeFiles/histogram.dir/histogram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/histogram.dir/histogram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/histogram.cpp" > CMakeFiles/histogram.dir/histogram.cpp.i

CMakeFiles/histogram.dir/histogram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/histogram.dir/histogram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/histogram.cpp" -o CMakeFiles/histogram.dir/histogram.cpp.s

# Object files for target histogram
histogram_OBJECTS = \
"CMakeFiles/histogram.dir/histogram.cpp.o"

# External object files for target histogram
histogram_EXTERNAL_OBJECTS =

histogram: CMakeFiles/histogram.dir/histogram.cpp.o
histogram: CMakeFiles/histogram.dir/build.make
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_gapi.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_highgui.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_ml.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_objdetect.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_photo.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_stitching.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_video.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_videoio.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_dnn.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_imgcodecs.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_calib3d.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_features2d.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_flann.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_imgproc.so.4.5.1
histogram: /media/kaveesha/New\ Volume/University/Academic/Semesters/Semester\ 4/Opencv/build/lib/libopencv_core.so.4.5.1
histogram: CMakeFiles/histogram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable histogram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/histogram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/histogram.dir/build: histogram

.PHONY : CMakeFiles/histogram.dir/build

CMakeFiles/histogram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/histogram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/histogram.dir/clean

CMakeFiles/histogram.dir/depend:
	cd "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram" "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram" "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram" "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram" "/media/kaveesha/New Volume/University/Academic/Semesters/Semester 4/Opencv/Tutorials/multithreading historgram/CMakeFiles/histogram.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/histogram.dir/depend


cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 2016/09/18 Some functions does not seem to work or difficult to use with non-default CMAKE_BINARY_DIR.  Commented out.
##Cmake is supposed to set these two variables.  However, it doesn't.
##Looks to be something to do with variable cache.  Variable cache is one of the design failures of cmake.
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/exe)

set(YS_COMMAND_BINARY_DIR ${CMAKE_BINARY_DIR}/exe)
set(YS_COMMAND_BINARY_DIR ${YS_COMMAND_BINARY_DIR} PARENT_SCOPE)


# If ysgl source files may not be placed under ${CMAKE_CURRENT_SOURCE_DIR}/src/ysgl/src, include_directories must be added here.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imported/include)


# Capture global-YS_LIBRARY_LIST into local YS_LIBRARY_LIST
set(YS_LIBRARY_LIST ${YS_LIBRARY_LIST})

add_subdirectory("ysclass/src")
add_subdirectory("ysgl/src")
add_subdirectory("ysbitmapfont/src")
add_subdirectory("fssimplewindow/src")
add_subdirectory("fslazywindow/src")
add_subdirectory("simplebitmap")


# Export include paths
foreach(ONE_LIBRARY ${YS_LIBRARY_LIST})
set(${ONE_LIBRARY}_INCLUDE_DIR ${${ONE_LIBRARY}_INCLUDE_DIR} PARENT_SCOPE)
endforeach(ONE_LIBRARY)

# Copy local-YS_LIBRARY_LIST back to global-YS_LIBRARY_LIST
set(YS_LIBRARY_LIST ${YS_LIBRARY_LIST} PARENT_SCOPE)

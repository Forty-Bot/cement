cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(cement)

# Generates compile_commands.json in the build dir
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#Enable debug target by default
if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "debug")
endif()

# Include extra modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Init LIBS
set(LIBS)

find_package(LibTCOD REQUIRED)
include_directories(${LibTCOD_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LIBTCOD_LIBRARIES})

# Add c99 flag
add_definitions(-std=c99)

add_subdirectory(res)
add_subdirectory(src)

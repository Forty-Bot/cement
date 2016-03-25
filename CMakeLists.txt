cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(cement CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

#Enable debug target by default
if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "debug")
endif()

# Include extra modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(res)
add_subdirectory(src)

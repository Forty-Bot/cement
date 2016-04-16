set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(executable_name cement)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
add_executable(${executable_name} ${sources})

# Find LibTCOD
find_package(LibTCOD REQUIRED)
include_directories(${LIBTCOD_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LIBTCOD_LIBRARIES})

# Find Lua
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LUA_LIBRARIES})

# Find Eigen
find_package(Eigen3 REQUIRED)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

target_link_libraries(${executable_name} ${LIBS})

# Set the standard to C++11
set(C_STANDARD_REQUIRED ON)
set_property(TARGET ${executable_name} PROPERTY CXX_STANDARD 11)

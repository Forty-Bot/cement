set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(executable_name cement)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
add_executable(${executable_name} ${sources})
target_link_libraries(${executable_name} ${LIBS})

# Set the standard to C++11
set(C_STANDARD_REQUIRED ON)
set_property(TARGET ${executable_name} PROPERTY CXX_STANDARD 11)

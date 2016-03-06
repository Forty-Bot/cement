set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(executable_name cement)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}" "*.c")
add_executable(${executable_name} ${sources})
target_link_libraries(${executable_name} ${LIBS})

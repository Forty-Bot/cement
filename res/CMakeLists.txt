file(GLOB files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.png")
foreach(file ${files})
	configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)
endforeach()

project("Glad")

add_library("Glad" "${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c")
target_include_directories("Glad" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

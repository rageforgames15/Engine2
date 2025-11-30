cmake_minimum_required(VERSION 4.1)

set(CMAKE_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)

project("Engine")

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad")

file(
  GLOB_RECURSE
  SRCS
  CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE
  Glad
  fmt::fmt
  ${OpenGL_LIBRARIES} glfw
  ${Stb_LIBRARIES}
)
target_include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include/
  ${Stb_INCLUDE_DIRS}
)

if(DEFINED ENV{PRODUCT_BUILD})
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PRODUCT_BUILD=1)
  message(STATUS "Product build")
endif()

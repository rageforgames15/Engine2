cmake_minimum_required(VERSION 4.1)

set(CMAKE_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)

project("Engine")
include(CheckIPOSupported)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LuaJIT REQUIRED IMPORTED_TARGET luajit)

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
  PkgConfig::LuaJIT
)
find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")
target_include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include/
  ${Stb_INCLUDE_DIRS}
  ${SOL2_INCLUDE_DIRS}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SOL_LUAJIT=1 SOL_USING_CXX_LUAJIT=1 SOL_NO_EXCEPTIONS=1)

if(MSVC)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

if(DEFINED ENV{PRODUCT_BUILD})
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PRODUCT_BUILD=1)
  message(STATUS "Product build")
endif()

check_ipo_supported(RESULT sup OUTPUT error)

message(STATUS ${sup})

if(sup)
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  message(STATUS "IPO ENABLED")
endif()

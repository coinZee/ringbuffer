cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "crb")
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(crb INTERFACE)

target_include_directories(crb INTERFACE 
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  add_executable(crb_example example.cpp)
  target_link_libraries(crb_example PRIVATE crb)
endif()

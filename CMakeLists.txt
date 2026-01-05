cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "crb")
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)

add_library(crb INTERFACE)

add_library(crb::crb ALIAS crb)

target_include_directories(crb INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(crb INTERFACE cxx_std_17)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  add_executable(crb_example example.cpp)
  target_link_libraries(crb_example PRIVATE crb::crb)
endif()

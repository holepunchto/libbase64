cmake_minimum_required(VERSION 3.22)

project(base64 C)

add_library(base64 OBJECT)

set_target_properties(
  base64
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  base64
  INTERFACE
    include/base64.h
  PRIVATE
    src/base64.c
)

target_include_directories(
  base64
  PUBLIC
    include
)

add_library(base64_shared SHARED $<TARGET_OBJECTS:base64>)

set_target_properties(
  base64_shared
  PROPERTIES
  OUTPUT_NAME base64
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

add_library(base64_static STATIC $<TARGET_OBJECTS:base64>)

set_target_properties(
  base64_static
  PROPERTIES
  OUTPUT_NAME base64
  PREFIX lib
)

install(TARGETS base64_shared base64_static)

install(FILES include/base64.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()

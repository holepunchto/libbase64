cmake_minimum_required(VERSION 3.22)

project(base64 C)

if(NOT TARGET utf)
  add_subdirectory(vendor/libutf EXCLUDE_FROM_ALL)
endif()

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
    $<TARGET_PROPERTY:utf,INTERFACE_INCLUDE_DIRECTORIES>
)

add_library(base64_shared SHARED)

set_target_properties(
  base64_shared
  PROPERTIES
  OUTPUT_NAME base64
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  base64_shared
  PUBLIC
    base64
)

add_library(base64_static STATIC)

set_target_properties(
  base64_static
  PROPERTIES
  OUTPUT_NAME base64
  PREFIX lib
)

target_link_libraries(
  base64_static
  PUBLIC
    base64
)

install(TARGETS base64_shared base64_static)

install(FILES include/base64.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()

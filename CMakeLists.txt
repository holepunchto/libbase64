cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-fuzz REQUIRED PATHS node_modules/cmake-fuzz)

project(base64 C)

fetch_package("github:holepunchto/libutf")

get_property(shared GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)

add_library(base64 OBJECT)

set_target_properties(
  base64
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ${shared}
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

if(shared)
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
endif()

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

install(TARGETS base64_static)

if(shared)
  install(TARGETS base64_shared)
endif()

install(FILES include/base64.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()

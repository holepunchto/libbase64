cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-fuzz REQUIRED PATHS node_modules/cmake-fuzz)
find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(base64 LANGUAGES C VERSION 0.0.0)

fetch_package("github:holepunchto/libutf")

add_library_targets(
  base64
  HEADERS
    include/base64.h
  FEATURES
    c_std_99
  SOURCES
    src/base64.c
  LINK
    utf::headers
)

add_test_subdirectory(test)

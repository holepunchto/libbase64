list(APPEND tests
  decode
  decode-invalid
  decode-length
  encode
  encode-length
)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.c)

  target_link_libraries(
    ${test}
    PRIVATE
      base64_static
  )

  target_include_directories(
    ${test}
    PRIVATE
      $<TARGET_PROPERTY:base64,INTERFACE_INCLUDE_DIRECTORIES>
  )

  add_test(
    NAME ${test}
    COMMAND ${test}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_tests_properties(
    ${test}
    PROPERTIES
    TIMEOUT 30
  )
endforeach()

if(TARGET base64_shared)
  set(library base64::shared)
else()
  set(library base64::static)
endif()

add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    ${library}
)

add_subdirectory(fuzz)

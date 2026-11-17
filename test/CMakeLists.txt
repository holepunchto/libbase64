add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    base64::<TYPE>
)

add_subdirectory(fuzz)

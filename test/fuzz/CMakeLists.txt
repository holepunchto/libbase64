add_fuzz_executables(
  encode/utf8.c
  encode/utf16le.c
  decode/utf8.c
  decode/utf16le.c
  PREFIX fuzz_
  LINK
    base64::static
)

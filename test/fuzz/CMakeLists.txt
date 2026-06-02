list(APPEND fuzzers
  encode/utf8
  encode/utf16le
  decode/utf8
  decode/utf16le
)

foreach(fuzzer IN LISTS fuzzers)
  string(REPLACE "/" "_" name ${fuzzer})

  add_fuzzer(fuzz_${name} ${fuzzer}.c)

  target_link_libraries(
    fuzz_${name}
    PRIVATE
      base64_static
  )
endforeach()

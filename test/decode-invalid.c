#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/base64.h"

#define test_decode_invalid(string) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = base64_decode_utf8((utf8_t *) string, string_len, buffer, &buffer_len); \
    assert(err != 0); \
  };

#define test_decode_invalid_utf16le(...) \
  { \
    utf16_t string[] = __VA_ARGS__; \
    size_t string_len = sizeof(string) / sizeof(utf16_t); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = base64_decode_utf16le(string, string_len, buffer, &buffer_len); \
    assert(err != 0); \
  };

int
main() {
  test_decode_invalid("a");
  test_decode_invalid("abc*");

  test_decode_invalid_utf16le({0x0041, 0x0042, 0x0043, 0x0100});
  test_decode_invalid_utf16le({0x0041, 0x0042, 0x0100});
  test_decode_invalid_utf16le({0xffff, 0xffff, 0xffff, 0xffff});
  test_decode_invalid_utf16le({0x0041, 0xd800, 0x0042, 0x0043});
}

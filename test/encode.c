#include <assert.h>
#include <string.h>

#include "../include/base64.h"

#define test_encode(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = 4 * ((buffer_len + 2) / 3) + 1; \
    char string[string_len]; \
    int err = base64_encode((uint8_t *) buffer, buffer_len, string, &string_len); \
    assert(err == 0); \
    assert(string_len == strlen(expected)); \
    assert(strncmp(string, expected, string_len) == 0); \
  };

int
main () {
  test_encode("a", "YQ==");
  test_encode("ab", "YWI=");
  test_encode("abc", "YWJj");
  test_encode("abcd", "YWJjZA==");
  test_encode("abcde", "YWJjZGU=");
}

#include <assert.h>
#include <string.h>

#include "../include/base64.h"

#define test_decode_length(string, expected) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = 0; \
    int err = base64_decode(string, string_len, NULL, &buffer_len); \
    assert(err == 0); \
    assert(buffer_len == expected); \
  };

int
main () {
  test_decode_length("YQ==", 1);
  test_decode_length("YWI=", 2);
  test_decode_length("YWJj", 3);
  test_decode_length("YWJjZA==", 4);
  test_decode_length("YWJjZGU=", 5);
}

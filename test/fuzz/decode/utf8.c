#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/base64.h"

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Decoded output is never larger than the input.
  size_t buffer_len = size;
  uint8_t *buffer = buffer_len > 0 ? malloc(buffer_len) : NULL;

  int err = base64_decode_utf8((const utf8_t *) data, size, buffer, &buffer_len);

  if (err == 0) {
    // Re-encode the decoded bytes; the result must decode back identically.
    size_t string_len = 4 * ((buffer_len + 2) / 3);
    utf8_t *string = string_len > 0 ? malloc(string_len) : NULL;

    size_t len = string_len;
    err = base64_encode_utf8(buffer, buffer_len, string, &len);

    assert(err == 0);
    assert(len == string_len);

    size_t roundtrip_len = buffer_len;
    uint8_t *roundtrip = roundtrip_len > 0 ? malloc(roundtrip_len) : NULL;

    err = base64_decode_utf8(string, string_len, roundtrip, &roundtrip_len);

    assert(err == 0);
    assert(roundtrip_len == buffer_len);

    if (buffer_len > 0) {
      assert(memcmp(roundtrip, buffer, buffer_len) == 0);
    }

    free(roundtrip);
    free(string);
  }

  free(buffer);

  return 0;
}

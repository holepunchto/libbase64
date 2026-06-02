#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/base64.h"

static void
roundtrip(const uint8_t *data, size_t size, const utf16_t *string, size_t string_len) {
  if (size == 0) return;

  size_t buffer_len = size;
  uint8_t *buffer = malloc(buffer_len);

  int err = base64_decode_utf16le(string, string_len, buffer, &buffer_len);

  assert(err == 0);
  assert(buffer_len == size);
  assert(memcmp(buffer, data, size) == 0);

  free(buffer);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Standard (padded) encoding.
  size_t padded_len = 4 * ((size + 2) / 3);
  utf16_t *padded = padded_len > 0 ? malloc(padded_len * sizeof(utf16_t)) : NULL;

  size_t len = padded_len;
  int err = base64_encode_utf16le(data, size, padded, &len);

  assert(err == 0);
  assert(len == padded_len);

  roundtrip(data, size, padded, padded_len);

  free(padded);

  // URL-safe (unpadded) encoding.
  size_t url_len = (size * 4 + 2) / 3;
  utf16_t *url = url_len > 0 ? malloc(url_len * sizeof(utf16_t)) : NULL;

  len = url_len;
  err = base64url_encode_utf16le(data, size, url, &len);

  assert(err == 0);
  assert(len == url_len);

  roundtrip(data, size, url, url_len);

  free(url);

  return 0;
}

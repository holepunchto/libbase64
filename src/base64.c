#include <math.h>
#include <stddef.h>

#include "../include/base64.h"

static const char base64_alphabet[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char base64_inverse_alphabet[256] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int
base64_encode (const uint8_t *buffer, size_t buffer_len, char *string, size_t *string_len) {
  size_t len = 4 * ((buffer_len + 2) / 3);

  if (string == NULL) {
    *string_len = len;
    return 0;
  }

  if (*string_len < len + 1) return -1;

  *string_len = len;

  size_t k = 0, i = 0, n = buffer_len;

  for (; i + 2 < n; i += 3) {
    string[k++] = base64_alphabet[buffer[i] >> 2];
    string[k++] = base64_alphabet[((buffer[i] & 0x03) << 4) | (buffer[i + 1] >> 4)];
    string[k++] = base64_alphabet[((buffer[i + 1] & 0x0f) << 2) | (buffer[i + 2] >> 6)];
    string[k++] = base64_alphabet[buffer[i + 2] & 0x3f];
  }

  if (i < n) {
    string[k++] = base64_alphabet[buffer[i] >> 2];

    if (i + 1 < n) {
      string[k++] = base64_alphabet[((buffer[i] & 0x03) << 4) | (buffer[i + 1] >> 4)];
      string[k++] = base64_alphabet[(buffer[i + 1] & 0x0f) << 2];
    } else {
      string[k++] = base64_alphabet[(buffer[i] & 0x03) << 4];
      string[k++] = '=';
    }

    string[k++] = '=';
  }

  string[k] = '\0';

  return 0;
}

int
base64_decode (const char *string, size_t string_len, uint8_t *buffer, size_t *buffer_len) {
  if (string_len % 4 != 0) return -1;

  if (string_len == 0) {
    *buffer_len = 0;
    return 0;
  }

  size_t len = string_len / 4 * 3;

  if (string[string_len - 1] == '=') len--;
  if (string[string_len - 2] == '=') len--;

  if (buffer == NULL) {
    *buffer_len = len;
    return 0;
  }

  if (*buffer_len < len) return -1;

  *buffer_len = len;

  size_t k = 0;

  for (size_t i = 0, n = string_len; i < n; i += 4) {
    char chunk[4];

    for (size_t j = 0; j < 4; j++) {
      chunk[j] = string[i + j] == '=' ? 0 : base64_inverse_alphabet[string[i + j]];

      if (chunk[j] == -1) return -1;
    }

    uint32_t triple = (chunk[0] << 3 * 6) + (chunk[1] << 2 * 6) + (chunk[2] << 1 * 6) + (chunk[3] << 0 * 6);

    if (k < len) buffer[k++] = (triple >> 2 * 8) & 0xFF;
    if (k < len) buffer[k++] = (triple >> 1 * 8) & 0xFF;
    if (k < len) buffer[k++] = (triple >> 0 * 8) & 0xFF;
  }

  return 0;
}

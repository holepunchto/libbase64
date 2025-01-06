#include <stdint.h>
#include <utf.h>

#include "../include/base64.h"

extern int
base64_encode_utf8(const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len);

extern int
base64_decode_utf8(const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);

extern int
base64_encode_utf16le(const uint8_t *buffer, size_t buffer_len, utf16_t *string, size_t *string_len);

extern int
base64_decode_utf16le(const utf16_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);

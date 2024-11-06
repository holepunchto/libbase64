#include <stdint.h>
#include <utf.h>

#include "../include/base64.h"

extern int
base64_encode (const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len);

extern int
base64_decode (const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);

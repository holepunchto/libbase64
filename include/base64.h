#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int
base64_encode (const uint8_t *buffer, size_t buffer_len, char *string, size_t *string_len);

int
base64_decode (const char *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);

#ifdef __cplusplus
}
#endif

#endif // BASE64_H

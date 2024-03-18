#include "Hex.h"

#include "../string/String.h"

size_t cHexToDec(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'f') return c - 'a' + 10;
    else if ('A' <= c && c <= 'F') return c - 'A' + 10;
    else return 0;
}

size_t Hex::FromString(const char *src) {
    if (src == nullptr) return 0;

    size_t index = 0;
    size_t result = 0;
    size_t length = String::Length(src);

    if (length < 2) return cHexToDec(src[0]);
    if (String::Compare("0x", src, 2)) index = 2;

    while (index < length) {
        result *= 16;
        result += cHexToDec(src[index]);
        ++index;
    }

    return result;
}

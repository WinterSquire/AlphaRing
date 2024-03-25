#include "String.h"

size_t String::Copy(char *dst, size_t bufferSize, const char *src) {
    if (dst == nullptr || bufferSize == 0 || src == nullptr) return 0;

    int index = 0;
    while (index < bufferSize - 1 && src[index] != '\0') {
        dst[index] = src[index];
        ++index;
    }
    dst[index] = '\0';

    return index;
}

size_t String::Length(const char *str) {
    if (str == nullptr) return 0;

    size_t length = 0;
    while (str[length] != '\0') ++length;

    return length;
}

size_t String::LengthS(const char *str, size_t max_length) {
    if (str == nullptr) return 0;

    size_t length = 0;
    while (length < max_length && str[length] != '\0') ++length;

    return length;
}

size_t String::Compare(const char *str1, const char *str2, size_t length) {
    for (int i = 0; i < length; ++i) {
        if (str1[i] == '\0' || str2[i] == '\0') return false;
        if (str1[i] != str2[i]) return false;
    }

    return true;
}

static size_t charToNum(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'f') return c - 'a' + 10;
    else if ('A' <= c && c <= 'F') return c - 'A' + 10;
    else return 0;
}

size_t String::ToNumber(const char *str, String::eBase base) {
    if (str == nullptr || base < 2 || base > 16) return 0;

    size_t index = 0;
    size_t result = 0;
    size_t length = Length(str);

    if (length < 1) return 0;

    switch (base) {
        case Hex:
            if (length >= 2 && Compare("0x", str, 2)) index = 2;
            break;
        default:
            break;
    }

    while (index < length) {
        result *= base;
        result += charToNum(str[index]);
        ++index;
    }

    return result;
}

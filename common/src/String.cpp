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

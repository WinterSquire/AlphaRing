#include "String.h"

size_t String::wstrcpy(wchar_t *dest, const wchar_t *src, size_t n) {
    size_t i = 0;
    for (; i < n; i++) {
        dest[i] = src[i];
        if (src[i] == L'\0') {
            break;
        }
    }
    return i;
}

size_t String::wstrcpy(wchar_t *dest, const char *src, size_t n) {
    size_t i = 0;
    for (; i < n; i++) {
        dest[i] = src[i];
        if (src[i] == '\0') {
            break;
        }
    }
    return i;
}

size_t String::strcpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    for (; i < n; i++) {
        dest[i] = src[i];
        if (src[i] == '\0') {
            break;
        }
    }
    return i;
}

size_t String::strcpy(char *dest, const wchar_t *src, size_t n) {
    size_t i = 0;
    for (; i < n; i++) {
        dest[i] = src[i];
        if (src[i] == L'\0') {
            break;
        }
    }
    return i;
}
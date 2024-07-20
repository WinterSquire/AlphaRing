#include "String.h"

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

void String::convert(char *dest, const wchar_t *src, size_t n) {
    auto str = converter.to_bytes(src);
    auto length = str.length() < n - 1 ? str.length() : n - 1;
    memcpy(dest, str.c_str(), length);
    dest[length] = '\0';
}

void String::convert(wchar_t *dest, const char *src, size_t n) {
    auto str = converter.from_bytes(src);
    auto length = str.length() < n - 1 ? str.length() : n - 1;
    memcpy(dest, str.c_str(), length * sizeof(wchar_t));
    dest[length] = L'\0';
}

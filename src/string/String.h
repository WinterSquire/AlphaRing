#ifndef TINYXML2_TEST_STRING_H
#define TINYXML2_TEST_STRING_H


namespace String {
    const size_t MAX_BUFFER_LENGTH = 1024;

    size_t Copy(char* dst, size_t bufferSize, const char* src);
    size_t Length(const char* str);
    size_t LengthS(const char* str, size_t max_length = MAX_BUFFER_LENGTH);
    size_t Compare(const char* str1, const char* str2, size_t length);

    enum eBase {
        Oct = 10,
        Hex = 16
    };

    size_t ToNumber(const char* str, eBase base);
};


#endif //TINYXML2_TEST_STRING_H

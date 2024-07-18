#pragma once

#include <string>

union FileVersion {
public:
    unsigned long long version;
    unsigned short bits[4];
    unsigned int dwFileVersion[2];

    explicit FileVersion() : version(0) {};
    explicit FileVersion(__int64 hModule);
    explicit FileVersion(const char *file);
    explicit FileVersion(const wchar_t *file);

    std::string toString();

    static FileVersion fromString(const char* str);
    static FileVersion fromFile(const char* file);
    static FileVersion fromFile(const wchar_t* file);

    inline void operator=(unsigned long long v) {version = v;};
    inline bool operator==(const FileVersion& v) {return version == v.version;};
    inline bool operator!=(const FileVersion& v) {return version != v.version;};
private:
    void set(void* info);

};

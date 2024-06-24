#pragma once

union FileVersion {
    unsigned long long version;
    unsigned short bits[4];
    unsigned int dwFileVersion[2];

    FileVersion() : version(0) {};
    FileVersion(__int64 hModule);
    FileVersion(const char *file);
    FileVersion(const wchar_t *file);

    void toString(char* buffer, size_t buffer_size);

    inline void operator=(unsigned long long v) {version = v;};
private:
    void set(void* info);

};

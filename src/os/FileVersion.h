#ifndef ALPHA_RING_FILEVERSION_H
#define ALPHA_RING_FILEVERSION_H

union FileVersion {
    unsigned long long version;
    unsigned short bits[4];
    unsigned int dwFileVersion[2];

    FileVersion();
    FileVersion(const char *file);
    FileVersion(const wchar_t *file);

    void toString(char* buffer, size_t buffer_size);
private:
    void set(void* info);

};

#endif //ALPHA_RING_FILEVERSION_H

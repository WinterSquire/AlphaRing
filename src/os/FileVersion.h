#ifndef ALPHA_RING_FILEVERSION_H
#define ALPHA_RING_FILEVERSION_H

#include <cstdint>
#include <string>

class FileVersion {
public:
    FileVersion(uint64_t version);
    FileVersion(const char* version);
    FileVersion(uint16_t a, uint16_t b, uint16_t c, uint16_t d);

    std::string toString() const;

    static FileVersion getFileVersion(const char *fileName);
private:
    uint64_t m_version;
};

#endif //ALPHA_RING_FILEVERSION_H

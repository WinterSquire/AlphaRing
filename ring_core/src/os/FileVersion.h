#ifndef TINYXML2_TEST_FILEVERSION_H
#define TINYXML2_TEST_FILEVERSION_H

#include "../system/Base.h"

class FileVersion {
public:
    FileVersion(uint64_t version);
    FileVersion(const char* version);
    FileVersion(uint16_t a, uint16_t b, uint16_t c, uint16_t d);

    string toString() const;

    static FileVersion getFileVersion(const char *fileName);
private:
    uint64_t m_version;
};

#endif //TINYXML2_TEST_FILEVERSION_H

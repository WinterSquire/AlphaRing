#include "FileVersion.h"

#include <Windows.h>

FileVersion::FileVersion(uint64_t version) {
    m_version = version;
}

FileVersion::FileVersion(const char *version) {
    char c;
    int index = 0;
    int dot_count = 0;
    int dots[3];

    while ((c = version[index]) && dot_count != 3) {
        if (c == '.') {
            dots[dot_count] = index;
            ++dot_count;
        }
        ++index;
    }

    FileVersion(std::stoi(string(version, dots[0])),
                std::stoi(string(version, dots[0], dots[1])),
                std::stoi(string(version, dots[1], dots[2])),
                std::stoi(string(version + dots[2]))
    );
}

FileVersion::FileVersion(uint16_t a, uint16_t b, uint16_t c, uint16_t d) {
    m_version = a;
    m_version = m_version << 16 | b;
    m_version = m_version << 16 | c;
    m_version = m_version << 16 | d;
}

string FileVersion::toString() const {
    char buffer[256];

    sprintf_s(buffer, "%d.%d.%d.%d",
              static_cast<uint16_t>(( m_version >> (32 + 16) ) & 0xffff),
              static_cast<uint16_t>(( m_version >> (32) ) & 0xffff),
              static_cast<uint16_t>(( m_version >> (16) ) & 0xffff),
              static_cast<uint16_t>(( m_version >> (0) ) & 0xffff)
    );

    return {buffer};
}

FileVersion FileVersion::getFileVersion(const char *fileName) {
    const int BLOCK_SIZE = 2048;
    char block[BLOCK_SIZE];

    UINT size;
    DWORD dwHandle;
    LPBYTE lpBuffer;
    DWORD dwLen = GetFileVersionInfoSizeA(fileName, &dwHandle);

    if (dwLen == NULL || dwLen > BLOCK_SIZE)
        return {static_cast<uint64_t>(-1)};

    if (!GetFileVersionInfoA(fileName, dwHandle, dwLen, block))
        return {static_cast<uint64_t>(-1)};

    if (!VerQueryValueA(block, "\\", (LPVOID*)&lpBuffer, &size))
        return {static_cast<uint64_t>(-1)};

    auto *fileInfo = (VS_FIXEDFILEINFO*) lpBuffer;

    if (fileInfo->dwSignature != 0xFEEF04BD)
        return {static_cast<uint64_t>(-1)};

    return {static_cast<uint64_t>(fileInfo->dwFileVersionMS) << 32 | fileInfo->dwFileVersionLS};
}

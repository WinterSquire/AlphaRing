#include "FileVersion.h"

#include <Windows.h>
#include <string>

FileVersion::FileVersion(const char *file) : FileVersion() {
    version = fromFile(file).version;
}

FileVersion::FileVersion(const wchar_t *file) : FileVersion() {
    version = fromFile(file).version;
}

FileVersion::FileVersion(__int64 hModule) {
    wchar_t str[2048];

    if (hModule == 0) return;

    if (GetModuleFileNameW((HMODULE)hModule, str, MAX_PATH) <= 0) return;

    version = fromFile(str).version;
}

void FileVersion::set(void *info) {
    auto *fileInfo = (VS_FIXEDFILEINFO*) info;
    if (fileInfo == nullptr || fileInfo->dwSignature != 0xfeef04bd) return;
    this->dwFileVersion[0] = fileInfo->dwFileVersionMS;
    this->dwFileVersion[1] = fileInfo->dwFileVersionLS;
}

std::string FileVersion::toString() {
    char buffer[32];
    sprintf_s(buffer, "%hd.%hd.%hd.%hd", bits[1], bits[0], bits[3], bits[2]);
    return std::string(buffer);
}

FileVersion FileVersion::fromString(const char *str) {
    FileVersion v;
    v.version = -1;

    sscanf_s(str, "%hd.%hd.%hd.%hd", &v.bits[1], &v.bits[0], &v.bits[3], &v.bits[2]);
    return v;
}

FileVersion FileVersion::fromFile(const wchar_t *file) {
    const int BLOCK_SIZE = 2048;
    wchar_t block[BLOCK_SIZE];
    FileVersion result;
    result.version = -1;

    UINT size;
    DWORD dwHandle;
    LPBYTE lpBuffer;
    DWORD dwLen = GetFileVersionInfoSizeW(file, &dwHandle);

    if (dwLen == NULL || dwLen > BLOCK_SIZE) return result;

    if (!GetFileVersionInfoW(file, dwHandle, dwLen, block)) return result;

    if (!VerQueryValueA(block, "\\", (LPVOID*)&lpBuffer, &size)) return result;

    result.set(lpBuffer);

    return result;
}

FileVersion FileVersion::fromFile(const char *file) {
    const int BLOCK_SIZE = 2048;
    char block[BLOCK_SIZE];
    FileVersion result;
    UINT size;
    DWORD dwHandle;
    LPBYTE lpBuffer;
    DWORD dwLen = GetFileVersionInfoSizeA(file, &dwHandle);

    result.version = -1;

    if (dwLen == NULL || dwLen > BLOCK_SIZE) return result;

    if (!GetFileVersionInfoA(file, dwHandle, dwLen, block)) return result;

    if (!VerQueryValueA(block, "\\", (LPVOID*)&lpBuffer, &size)) return result;

    result.set(lpBuffer);

    return result;
}

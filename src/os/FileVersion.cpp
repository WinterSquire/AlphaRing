#include "FileVersion.h"

#include <Windows.h>
#include <string>

FileVersion::FileVersion() : version(0) {

}

FileVersion::FileVersion(const char *file) : FileVersion() {
    const int BLOCK_SIZE = 2048;
    char block[BLOCK_SIZE];

    UINT size;
    DWORD dwHandle;
    LPBYTE lpBuffer;
    DWORD dwLen = GetFileVersionInfoSizeA(file, &dwHandle);

    if (dwLen == NULL || dwLen > BLOCK_SIZE) return;

    if (!GetFileVersionInfoA(file, dwHandle, dwLen, block)) return;

    if (!VerQueryValueA(block, "\\", (LPVOID*)&lpBuffer, &size)) return;

    set(lpBuffer);
}

FileVersion::FileVersion(const wchar_t *file) : FileVersion() {
    const int BLOCK_SIZE = 2048;
    wchar_t block[BLOCK_SIZE];

    UINT size;
    DWORD dwHandle;
    LPBYTE lpBuffer;
    DWORD dwLen = GetFileVersionInfoSizeW(file, &dwHandle);

    if (dwLen == NULL || dwLen > BLOCK_SIZE) return;

    if (!GetFileVersionInfoW(file, dwHandle, dwLen, block)) return;

    if (!VerQueryValueA(block, "\\", (LPVOID*)&lpBuffer, &size)) return;

    set(lpBuffer);
}

void FileVersion::set(void *info) {
    auto *fileInfo = (VS_FIXEDFILEINFO*) info;
    if (fileInfo == nullptr || fileInfo->dwSignature != 0xfeef04bd) return;
    this->dwFileVersion[0] = fileInfo->dwFileVersionMS;
    this->dwFileVersion[1] = fileInfo->dwFileVersionLS;
}

void FileVersion::toString(char *buffer, size_t buffer_size) {
    sprintf_s(buffer, buffer_size, "%hd.%hd.%hd.%hd", bits[1], bits[0], bits[3], bits[2]);
}

#include "FileVersion.h"

#include <Windows.h>
#include <string>

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

FileVersion::FileVersion(__int64 hModule) : FileVersion() {
    if (hModule == 0) return;

    auto pDosHeader = (PIMAGE_DOS_HEADER)hModule;
    auto pNtHeader = (PIMAGE_NT_HEADERS)(hModule + pDosHeader->e_lfanew);
    auto pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)&pNtHeader->OptionalHeader;
    auto dataDirectory2 = (PIMAGE_DATA_DIRECTORY)&pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];
    auto pRes = (PIMAGE_RESOURCE_DIRECTORY)(hModule + dataDirectory2->VirtualAddress);

    // todo
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

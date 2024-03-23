#include "ThreadLocalStorage.h"

#include <windows.h>

#include <winnt.h>
#include <winternl.h>

static int getModuleTlsIndex(__int64 pModule) {
    if (pModule == 0) return 0;

    auto pDosHeader = (PIMAGE_DOS_HEADER)pModule;

    auto pNtHeader = (PIMAGE_NT_HEADERS)(pModule + pDosHeader->e_lfanew);

    auto pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)&pNtHeader->OptionalHeader;

    auto dataDirectory = (PIMAGE_DATA_DIRECTORY)&pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS];

    auto pTLS = (PIMAGE_TLS_DIRECTORY)(pModule + dataDirectory->VirtualAddress);

    return *(__int32*)pTLS->AddressOfIndex;
}

__int64* ThreadLocalStorage::ptr(int index) {
    return *(m_pTLS + m_TlsIndex) + index;
}

__int64 ThreadLocalStorage::operator[](int index) {
    return (*(m_pTLS + m_TlsIndex))[index];
}

bool ThreadLocalStorage::update(__int64 pModule) {
    if (pModule == 0) return false;

    m_pTEB = (__int64*)NtCurrentTeb();
    m_pTLS = (__int64**)((_TEB*)m_pTEB)->Reserved1[11];
    m_TlsIndex = getModuleTlsIndex(pModule);

    return true;
}

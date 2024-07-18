#pragma once

struct ThreadLocalStorage {
public:
    bool update(const char* moduleName);
    bool update(__int64 pModule);

    __int64 operator[] (int index);

    __int64* ptr (int index);

    __int64* m_pTEB;
    __int64** m_pTLS;
    __int64 m_hModule;
    __int32 m_TlsIndex;
};

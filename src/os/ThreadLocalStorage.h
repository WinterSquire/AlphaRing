#ifndef ALPHA_RING_THREADLOCALSTORAGE_H
#define ALPHA_RING_THREADLOCALSTORAGE_H


struct ThreadLocalStorage {
public:
    bool update(__int64 pModule);

    __int64 operator[] (int index);

    __int64* ptr (int index);

    __int64* m_pTEB;
    __int64** m_pTLS;
    __int64 m_hModule;
    __int32 m_TlsIndex;
};


#endif //ALPHA_RING_THREADLOCALSTORAGE_H

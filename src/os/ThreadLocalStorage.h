#ifndef ALPHA_RING_THREADLOCALSTORAGE_H
#define ALPHA_RING_THREADLOCALSTORAGE_H


class ThreadLocalStorage {
public:
    bool update(__int64 pModule);

    __int64 operator[] (int index);

    __int64* ptr (int index);

    inline __int64* get_pTEB() const {return m_pTEB;};
    inline __int64** get_pTLS() const{return m_pTLS;};
    inline __int64 get_hModule() const{return m_hModule;};
    inline __int32 get_TlsIndex() const{return m_TlsIndex;};

private:
    __int64* m_pTEB;
    __int64** m_pTLS;
    __int64 m_hModule;
    __int32 m_TlsIndex;

};


#endif //ALPHA_RING_THREADLOCALSTORAGE_H

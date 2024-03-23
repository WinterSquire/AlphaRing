#ifndef ALPHA_RING_THREADLOCALSTORAGE_H
#define ALPHA_RING_THREADLOCALSTORAGE_H


class ThreadLocalStorage {
public:
    ThreadLocalStorage(__int64 pModule);

    __int64 operator[] (int index);

    __int64* ptr(int index);

private:
    __int64* m_pTEB;
    __int64** m_pTLS;
    __int32 m_TlsIndex;

};


#endif //ALPHA_RING_THREADLOCALSTORAGE_H

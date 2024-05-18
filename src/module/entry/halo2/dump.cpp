//#include "./Halo2.h"
//
//#include <cstdio>
//#include <cstring>
//
//namespace Halo2::Entry::Dump {
//    void detour(void *a1, unsigned __int8 a2, void* a3);
//
//    Halo2Entry(entry, 0x69DCB0, detour);
//}
//
//void Halo2::Entry::Dump::detour(void *a1, unsigned __int8 a2, void* a3) {
//    typedef void (__fastcall* func_t)(void *a1, unsigned __int8 a2, void* a3);
//    auto func = (func_t)entry.m_pOriginal;
//
//    auto file = fopen("D:\\Halo2Dump.dat", "wb+");
//    fwrite(a3, 1, 0xD4, file);
//    fclose(file);
//
//    func(a1, a2, a3);
//}

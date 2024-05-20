#ifndef ALPHA_RING_STRING_H
#define ALPHA_RING_STRING_H


namespace String {
    size_t wstrcpy(wchar_t *dest, const wchar_t *src, size_t n);
    template <size_t _Size> inline size_t wstrcpy(wchar_t (&dest)[_Size], const wchar_t *src) {return wstrcpy(dest, src, _Size);}
    size_t wstrcpy(wchar_t *dest, const char *src, size_t n);
    template <size_t _Size> inline size_t wstrcpy(wchar_t (&dest)[_Size], const char *src) {return wstrcpy(dest, src, _Size);}
    size_t strcpy(char *dest, const char *src, size_t n);
    template <size_t _Size> inline size_t strcpy(char (&dest)[_Size], const char *src) {return strcpy(dest, src, _Size);}
    size_t strcpy(char *dest, const wchar_t *src, size_t n);
    template <size_t _Size> inline size_t strcpy(char (&dest)[_Size], const wchar_t *src) {return strcpy(dest, src, _Size);}
}


#endif //ALPHA_RING_STRING_H

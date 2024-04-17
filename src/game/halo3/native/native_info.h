#ifndef ALPHA_RING_NATIVE_INFO_H
#define ALPHA_RING_NATIVE_INFO_H


class ICNativeInfo {
public:
    virtual bool setModuleAddress(__int64 hModule) = 0;
    virtual __int64 getModuleAddress() = 0;
    virtual __int64 getEntryAddress(int index) = 0;
};

extern ICNativeInfo* g_pICNativeInfo;
inline ICNativeInfo* NativeInfo() { return g_pICNativeInfo; }


#endif //ALPHA_RING_NATIVE_INFO_H

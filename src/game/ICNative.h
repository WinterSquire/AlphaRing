#pragma once

#include "core/ThreadLocalStorage.h"

class CNativeInfo {
public:
    bool update(const char* moduleName) {return m_tls.update(moduleName);}
    bool update(__int64 hModule) {return m_tls.update(hModule);}
    __int64 getModuleAddress() {return m_tls.m_hModule;}
    __int64 getEntryAddress(int index) {return m_tls[index];}

private:
    ThreadLocalStorage m_tls;

};

class ICNative {
public:
    virtual CNativeInfo* NativeInfo() = 0;

};

#define DefNative(name) \
    namespace name::Native { extern CNativeInfo s_nativeInfo;} \
    namespace name::Native

#define DefEntry(name, index) \
        struct name##_t;      \
        inline name##_t* name() {return (name##_t*)s_nativeInfo.getEntryAddress(index);} \
        struct name##_t

#define DefPtr(name, offset) \
        struct name##_t;      \
        inline name##_t* name() {return (name##_t*)(s_nativeInfo.getModuleAddress() + offset);} \
        struct name##_t

#define DefPPtr(name, offset1, offset2) \
        struct name##_t;      \
        inline name##_t* name() {return (name##_t*)(*(__int64*)(s_nativeInfo.getModuleAddress() + offset1) + offset2);} \
        struct name##_t

#define DefEntryEntity(name, index) \
        struct name##_t;             \
        inline entity_manager_t<name##_t>* name() {return (entity_manager_t<name##_t>*)s_nativeInfo.getEntryAddress(index);} \
        struct name##_t

#pragma once

#include "utils.h"

#define DefNative(name) \
    namespace name::Native { \
        extern ThreadLocalStorage s_nativeInfo; \
        namespace Function {                                                      \
            template<typename return_type, typename... Args>                            \
            inline return_type INVOKE(__int64 offset, Args... args) {                   \
                typedef return_type (__fastcall* func_t)(...);                          \
                return ((func_t)(Native::s_nativeInfo.m_hModule + offset))(args...);      \
            }                                                                           \
        }                                                                               \
    }                      \
    namespace name::Native

#define DefPtr(name, offset) \
        struct name##_t;      \
        inline name##_t* name() {return (name##_t*)(s_nativeInfo.m_hModule + offset);} \
        struct name##_t

#define DefPPtr(name, offset1, offset2) \
        struct name##_t;      \
        inline name##_t* name() {return (name##_t*)(*(__int64*)(s_nativeInfo.m_hModule + offset1) + offset2);} \
        struct name##_t

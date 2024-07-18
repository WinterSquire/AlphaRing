#pragma once

#include <initializer_list>

#define DefDetourFunction(return_type, call_type, name, ...) \
    static return_type (call_type *ppOriginal_##name)(__VA_ARGS__); \
    static return_type call_type name(__VA_ARGS__)

namespace AlphaRing::Hook {
    struct DetourFunction {
        const char* function_name;
        void** ppOriginal;
        void* detour;
    };

    struct DetourOffset {
        __int64 offset_steam;
        __int64 offset_ws;
        void* detour;
        void** ppOriginal;
    };

    struct FunctionOffset {
        __int64 offset_steam;
        __int64 offset_ws;
        void** ppFunction;
    };

    struct PatchFunction {
        const char* function_name;
        const char* patch;
        size_t size;
    };

    struct PatchMCC {
        __int64 offset_steam;
        __int64 offset_ws;
        const char* patch;
        size_t size;
    };

    struct Detour_t {
        void* pTarget;
        void* detour;
        void** ppOriginal;
    };

    bool Initialize();
    bool Shutdown();

    bool IsWS();

    bool Detour(const std::initializer_list<Detour_t>& hooks);
    bool Detour(const std::initializer_list<DetourOffset>& hooks);
    bool Detour(const char* module_name, const std::initializer_list<DetourFunction>& hooks);
    void Offset(const std::initializer_list<FunctionOffset>& offsets);
    bool Patch(const char* module_name, const std::initializer_list<PatchFunction>& patches);
    bool Patch(const std::initializer_list<PatchMCC>& patches);
}
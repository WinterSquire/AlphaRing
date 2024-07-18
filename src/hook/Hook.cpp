#include "Hook.h"

#include "common.h"

#include "utils.h"
#include "MinHook.h"

namespace AlphaRing::Hook {
    enum eDistro {
        Steam,
        WindowsStore,
        None
    };

    static eDistro distro;
    static __int64 hModule;
    static FileVersion version;

    bool IsWS() {
        return distro == WindowsStore;
    }

    bool Initialize() {
        bool result;
        char buffer[1024];

        result = MH_Initialize() == MH_OK;

        assertm(result, "failed to initialize minhook");

        if ((hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe")) != 0) {
            distro = Steam;
        } else if ((hModule = (__int64)GetModuleHandleA("MCCWinStore-Win64-Shipping.exe")) != 0) {
            distro = WindowsStore;
        } else {
            distro = None;
        }

        assertm(distro != None, "failed to get distro type");

        if ((version = FileVersion(hModule)) != FileVersion::fromString(GAME_VERSION)) {
            sprintf(buffer, "Version mismatch [%s]:%s", GAME_VERSION, version.toString().c_str());
            MessageBoxA(nullptr, buffer, "Error", MB_OK);
            return false;
        }

        return true;
    }

    bool Shutdown() {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();

        return true;
    }

    bool Detour(const std::initializer_list<Detour_t> &hooks) {
        for (auto &hook : hooks) {
            if (MH_CreateHook(hook.pTarget, hook.detour, hook.ppOriginal) != MH_OK ||
                MH_EnableHook(hook.pTarget) != MH_OK)
                return false;
        }
        return true;
    }

    bool Detour(const std::initializer_list<DetourOffset>& hooks) {
        void* pTarget;

        for (auto &hook : hooks) {
            if ((pTarget = (LPVOID) (hModule + (IsWS() ? hook.offset_ws : hook.offset_steam))),
                    MH_CreateHook(pTarget, hook.detour, hook.ppOriginal) != MH_OK ||
                    MH_EnableHook(pTarget) != MH_OK)
                return false;
        }
        return true;
    }

    bool Detour(const char *module_name, const std::initializer_list<DetourFunction>& hooks) {
        auto hModule = GetModuleHandleA(module_name);

        if (hModule == nullptr)
            return false;

        for (auto &hook : hooks) {
            auto pTarget = GetProcAddress(hModule, hook.function_name);

            if (pTarget == nullptr)
                return false;

            if (MH_CreateHook(pTarget, hook.detour, hook.ppOriginal) != MH_OK ||
                MH_EnableHook(pTarget) != MH_OK)
                return false;
        }

        return true;
    }

    void Offset(const std::initializer_list<FunctionOffset> &offsets) {
        for (auto &offset : offsets) {
            if (offset.ppFunction == nullptr) continue;
            *offset.ppFunction = (void*)(hModule + (IsWS() ? offset.offset_ws : offset.offset_steam));
        }
    }

    bool Patch(const char *module_name, const std::initializer_list<PatchFunction> &patches) {
        auto hModule = GetModuleHandleA(module_name);

        if (hModule == nullptr)
            return false;

        for (auto &patch : patches) {
            auto pTarget = (LPVOID)GetProcAddress(hModule, patch.function_name);

            if (pTarget == nullptr)
                return false;

            DWORD dwOldProtect;
            VirtualProtect(pTarget, patch.size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
            memcpy(pTarget, patch.patch, patch.size);
            VirtualProtect(pTarget, patch.size, dwOldProtect, &dwOldProtect);
        }

        return true;
    }

    bool Patch(const std::initializer_list<PatchMCC> &patches) {
        for (auto &patch : patches) {
            auto pTarget = (LPVOID)(hModule + (IsWS() ? patch.offset_ws : patch.offset_steam));

            DWORD dwOldProtect;
            VirtualProtect(pTarget, patch.size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
            memcpy(pTarget, patch.patch, patch.size);
            VirtualProtect(pTarget, patch.size, dwOldProtect, &dwOldProtect);
        }

        return true;
    }
}

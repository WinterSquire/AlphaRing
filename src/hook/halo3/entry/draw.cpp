#include "entry.h"

#include "hook/d3d11/imgui_impl.h"
#include <CommonStates.h>

namespace Halo3::Entry::Draw {
    const __int64 OFFSET = 0x2A33EC;
    extern void Prologue();
    extern void Epilogue();
    __int64 detour(__int64 *a1, unsigned int a2, __int64 a3, unsigned int a4, unsigned int a5);

    ::Entry entry{OFFSET, (__int64)detour};
}

static bool bWireframe = false;

__int64 __fastcall Halo3::Entry::Draw::detour(
        __int64 *a1,
        unsigned int a2,
        __int64 a3,
        unsigned int a4,
        unsigned int a5)
{
    typedef __int64 (__fastcall* func_t)(__int64 *a1, unsigned int a2, __int64 a3, unsigned int a4, unsigned int a5);
    auto func = (func_t)entry.getPointerOriginal();

    auto hModule = ::Entry::gethModule();
    auto pDevice = *(ID3D11Device**)(hModule + 0x46BA830);
    auto pContext = *(ID3D11DeviceContext**)(hModule + 0x46BA828);

    std::unique_ptr<DirectX::CommonStates> states = std::make_unique<DirectX::CommonStates>(pDevice);
    pContext->RSSetState(states->Wireframe());

    return func(a1, a2, a3, a4, a5);
}

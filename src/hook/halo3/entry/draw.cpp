#include "entry.h"

#include "hook/d3d11/imgui_impl.h"

#include <mutex>

static std::mutex mutex;

namespace Halo3::Entry::Draw {
    const __int64 OFFSET = 0x2A33EC;
    extern void Prologue();
    extern void Epilogue();
    __int64 detour(__int64 *a1, unsigned int a2, __int64 a3, unsigned int a4, unsigned int a5);
    bool bWireframe = false;

    bool getWireFrame() {
        std::lock_guard<std::mutex> lock(mutex);
        return bWireframe;
    }

    void setWireFrame(bool value) {
        std::lock_guard<std::mutex> lock(mutex);
        bWireframe = value;
    }

    ::Entry entry{OFFSET, (__int64)detour};
}


__int64 __fastcall Halo3::Entry::Draw::detour(
        __int64 *a1,
        unsigned int a2,
        __int64 a3,
        unsigned int a4,
        unsigned int a5)
{
    typedef __int64 (__fastcall* func_t)(__int64 *a1, unsigned int a2, __int64 a3, unsigned int a4, unsigned int a5);
    auto func = (func_t)entry.getPointerOriginal();

    {
        std::lock_guard<std::mutex> lock(mutex);
        if (bWireframe) {
            auto hModule = ::Entry::gethModule();
            auto pDevice = *(ID3D11Device**)(hModule + 0x46BA830);
            auto pContext = *(ID3D11DeviceContext**)(hModule + 0x46BA828);

            const D3D11_RASTERIZER_DESC desc {
                    D3D11_FILL_WIREFRAME,D3D11_CULL_NONE,false,
                    0,0.0f,0.0f,
                    true, false, false, false
            };
            ID3D11RasterizerState *pRasterizerState;

            pDevice->CreateRasterizerState(&desc, &pRasterizerState);
            pContext->RSSetState(pRasterizerState);
        }
    }

    return func(a1, a2, a3, a4, a5);
}

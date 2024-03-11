#ifndef DETOUR_FUNCTION_H
#define DETOUR_FUNCTION_H

#include <d3d11.h>

namespace Detour {
    HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    HRESULT ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
}

#endif //DETOUR_FUNCTION_H

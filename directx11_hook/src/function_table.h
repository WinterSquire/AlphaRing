#ifndef ALPHA_RING_FUNCTION_TABLE_H
#define ALPHA_RING_FUNCTION_TABLE_H

#include <d3d11.h>

// 8 13
typedef HRESULT(__stdcall* tPresent) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT (__stdcall* tResizeBuffers) (IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

struct FunctionTable {
    uintptr_t functions1[8];
    tPresent Present;
    uintptr_t functions2[4];
    tResizeBuffers ResizeBuffers;
    uintptr_t functions3[191];
};

#endif //ALPHA_RING_FUNCTION_TABLE_H

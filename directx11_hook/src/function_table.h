#ifndef ALPHA_RING_FUNCTION_TABLE_H
#define ALPHA_RING_FUNCTION_TABLE_H

#include <d3d11.h>

typedef HRESULT(__stdcall* tPresent) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT (__stdcall* tResizeBuffers) (IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

inline struct FunctionTable {
    uintptr_t functions[205];

    tPresent Present;
    tResizeBuffers ResizeBuffers;

    bool Initialize();
} functionTable;

#endif //ALPHA_RING_FUNCTION_TABLE_H

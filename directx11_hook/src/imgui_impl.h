#ifndef IMGUI_IMPL_H
#define IMGUI_IMPL_H

#include <d3d11.h>

namespace ImmediateGUI {
    bool Initialized();
    void Initialize(IDXGISwapChain *pSwapChain);
    void Update();
    void ReleaseMainRenderTargetView();
    void CreateMainRenderTargetView();
    ID3D11DeviceContext* GetImmediateContext();
};



#endif //IMGUI_IMPL_H

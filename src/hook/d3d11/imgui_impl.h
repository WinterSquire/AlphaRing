#ifndef IMGUI_IMPL_H
#define IMGUI_IMPL_H

#include <d3d11.h>

namespace ImmediateGUI {
    using IMGUIContextCallback_t = void(*)();

    void SetCallback(IMGUIContextCallback_t callback);

    bool Initialized();
    void Initialize(IDXGISwapChain *pSwapChain);
    void Update();
    void ReleaseMainRenderTargetView();
    void CreateMainRenderTargetView();

    void Render();
    void NewFrame();
    bool isVisible();

    IDXGISwapChain* GetSwapChain();
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetImmediateContext();
    ID3D11RenderTargetView** GetTargetView();

    void NewFrame();
};



#endif //IMGUI_IMPL_H

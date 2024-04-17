#include "detour_function.h"

#include "imgui_impl.h"
#include "function_table.h"

#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace SimpleMath;

std::unique_ptr<PrimitiveBatch<VertexPositionColor>> primitiveBatch;

std::unique_ptr<BasicEffect> basicEffect;

ID3D11InputLayout* inputLayout = NULL;

struct Vertex {float x,y,z; unsigned int rgba;};

const Vertex vertexs[] {
        {0.0f, 0.0f, 0.0f, 0xff00ffff},
        {1.0f, 1.0f, 0.0f, 0xff00ffff}
};

ID3D11Buffer* pBuffer;

void drawInit() {
    HRESULT hr = S_OK;
    void const* shaderByteCode;
    size_t byteCodeLength;

    auto pContext = ImmediateGUI::GetImmediateContext();
    auto pDevice = ImmediateGUI::GetDevice();

    primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(pContext);

    basicEffect = std::make_unique<BasicEffect>(pDevice);

    basicEffect->SetVertexColorEnabled(true);

    basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

    hr = pDevice->CreateInputLayout(
            VertexPositionColor::InputElements,
            VertexPositionColor::InputElementCount,
            shaderByteCode, byteCodeLength,
            &inputLayout
    );

    if (FAILED(hr)) {
        printf("Unable to create device input layout; result = %d\n", hr);
        return;
    }
}

void drawTest() {
    auto pContext = ImmediateGUI::GetImmediateContext();
    auto pDevice = ImmediateGUI::GetDevice();

    std::unique_ptr<CommonStates> states = std::make_unique<CommonStates>(pDevice);

    pContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
    pContext->OMSetDepthStencilState(states->DepthNone(), 0);
    pContext->RSSetState(states->CullNone());

    basicEffect->Apply(pContext);
    pContext->IASetInputLayout(inputLayout);

    primitiveBatch->Begin();

    primitiveBatch->DrawTriangle(
            VertexPositionColor(Vector3(0.f, 0.5f, 0.5f), Colors::Red),
            VertexPositionColor(Vector3(0.5f, -0.5f, 0.5f), Colors::Green),
            VertexPositionColor(Vector3(-0.5f, -0.5f, 0.5f), Colors::Blue)
    );

    primitiveBatch->End();
}

HRESULT __stdcall Detour::Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!ImmediateGUI::Initialized()) {
        ImmediateGUI::Initialize(pSwapChain);
        drawInit();
    }

    drawTest();

    ImmediateGUI::Update();

    return functionTable.Present(pSwapChain, SyncInterval, Flags);
}

HRESULT Detour::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    ImmediateGUI::ReleaseMainRenderTargetView();

    HRESULT hr = functionTable.ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    ImmediateGUI::CreateMainRenderTargetView();

    // Set up the viewport.
    D3D11_VIEWPORT vp{
        0,0,
        static_cast<FLOAT>(Width), static_cast<FLOAT>(Height),
        0.0f, 1.0f
    };

    ImmediateGUI::GetImmediateContext()->RSSetViewports(1, &vp);

    return hr;
}
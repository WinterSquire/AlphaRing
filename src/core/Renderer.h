#pragma once

#include <d3d11.h>

#include "Window.h"

class CRenderer {
    friend class CWindow;

public:
    CRenderer(CWindow* pWindow) {
        m_window = pWindow;
    }

    virtual bool Render() = 0;
    virtual bool Present() = 0;

protected:
    CWindow* m_window;

    IDXGISwapChain*         m_pSwapChain;
    ID3D11Device*			m_pDevice;
    ID3D11DeviceContext*	m_pContext;

};
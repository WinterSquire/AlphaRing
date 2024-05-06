#ifndef ALPHA_RING_RENDERER_H
#define ALPHA_RING_RENDERER_H


class ICRenderer {
public:
    virtual void Init(void* oWindow, void* p_swapChain, void* p_device, void* p_context) = 0;
    virtual void CreateMainRenderTargetView() = 0;
    virtual void ReleaseMainRenderTargetView() = 0;
    virtual void NewFrame() = 0;
    virtual void Render() = 0;
    virtual void EndFrame() = 0;
    virtual void Resize(float width, float height) = 0;
    virtual bool& ShowContext() = 0;

    virtual void SetState(void* p_state) = 0;
    virtual void SetStateWireframe() = 0;
};

extern ICRenderer *g_pRenderer;
inline ICRenderer* Renderer() { return g_pRenderer; }

#endif //ALPHA_RING_RENDERER_H

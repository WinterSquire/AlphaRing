#ifndef ALPHA_RING_DIRECTX11_HOOK_H
#define ALPHA_RING_DIRECTX11_HOOK_H


namespace Directx11Hook {
    bool Initialize();
    bool Shutdown();
}

namespace ImmediateGUI {
    using IMGUIContextCallback_t = void (*)();

    void SetCallback(IMGUIContextCallback_t callback);
}


#endif //ALPHA_RING_DIRECTX11_HOOK_H

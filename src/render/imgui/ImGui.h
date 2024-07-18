#pragma once

namespace AlphaRing::Render::ImGui {
    bool Initialize();

    enum {None, Halo1, Halo2, Halo3, Halo3ODST, HaloReach, Halo4,};

    void Render(int render_flag = None);

    bool BeginFrame();
    void EndFrame();
}
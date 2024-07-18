#pragma once

namespace AlphaRing::Render {
    bool Initialize();

    enum {None, Halo1, Halo2, Halo3, Halo3ODST, HaloReach, Halo4,};

    bool Render(int render_flag = None);

    void SetStateWireframe();
    void SetState(void *p_state);
}
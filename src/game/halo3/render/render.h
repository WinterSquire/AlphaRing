#pragma once

namespace Halo3::Render {
    struct WireFrame_t {
        bool model;
        bool structure;
    };

    WireFrame_t* WireFrame();
}
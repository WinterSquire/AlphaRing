#include "render.h"

static Halo3::Render::WireFrame_t s_data;

Halo3::Render::WireFrame_t *Halo3::Render::WireFrame() {
    return &s_data;
}
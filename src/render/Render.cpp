#include "Render.h"

#include "D3d11/D3d11.h"

bool AlphaRing::Render::Initialize() {
    return AlphaRing::Render::D3d11::Initialize();
}

void AlphaRing::Render::SetStateWireframe() {
    Graphics()->SetWireframe();
}

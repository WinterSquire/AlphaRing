#include "common.h"

#include "../native/native.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

struct Vertex {float x,y,z;unsigned int rgba;};

const Vertex vertex[] {
        {0, 0, 6, 0xff00ff00},
        {0, 1, 6, 0xff00ff00},

        {0, 0, 6, 0xff00ff00},
        {1, 0, 6, 0xff00ff00},

        {1, 0, 6, 0xff00ff00},
        {0, 1, 6, 0xff00ff00},
};

void Halo3::Entry::Render::Prologue() {

}

void Halo3::Entry::Render::Epilogue() {
    NativeFunc()->draw_line((void *)vertex, 3, sizeof(Vertex));
}

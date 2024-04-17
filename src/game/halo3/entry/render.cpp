#include "common.h"

#include "../native/native.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

struct Vertex {
    float x,y,z;
    unsigned int rgba;
};

const Vertex vertex[] {
        {-0.347, -19.447, 5.936, 0xff00ff00},
        {-0.347, -19.447, 10, 0xff00ff00},
};

void Halo3::Entry::Render::Prologue() {

}

void Halo3::Entry::Render::Epilogue() {
    NativeFunc()->draw(1, 1, (void *) vertex, sizeof(Vertex));
}

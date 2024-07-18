#include "CHalo3Context.h"

CHalo3Context CHalo3Context::instance;
ICContext* g_pHalo3Context = &CHalo3Context::instance;

void CHalo3Context::render() {
    context_global();
    context_actor();
    context_camera();
    context_object();
    context_physics();
    context_player();
    context_render();
}

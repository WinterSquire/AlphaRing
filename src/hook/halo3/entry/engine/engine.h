#ifndef ALPHA_RING_ENGINE_H
#define ALPHA_RING_ENGINE_H


namespace Halo3Hook::Engine {
    using callback_t = void(*)();
    void setInitCallback(callback_t func);
    void setUninitCallback(callback_t func);
}


#endif //ALPHA_RING_ENGINE_H

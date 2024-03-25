#ifndef ALPHA_RING_WORLD_H
#define ALPHA_RING_WORLD_H


namespace Halo3Hook::World{
    using callback_t = void(*)();
    void setInitCallback(callback_t func);
    void setUninitCallback(callback_t func);
};


#endif //ALPHA_RING_WORLD_H

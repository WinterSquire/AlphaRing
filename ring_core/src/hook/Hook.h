#ifndef ALPHA_RING_HOOK_H
#define ALPHA_RING_HOOK_H


namespace Hook {
    bool Init();
    bool Check(__int64 hModule);
    void Shutdown();
};


#endif //ALPHA_RING_HOOK_H

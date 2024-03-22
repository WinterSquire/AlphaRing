
#ifndef ALPHA_RING_MCC_H
#define ALPHA_RING_MCC_H

struct ModuleInfo {
    enum eTitle : __int32 {
        Halo1 = 0,
        Halo2 = 1,
        Halo3 = 2,
        Halo4 = 3,
        Groundhog = 4,
        Halo3ODST = 5,
        HaloReach = 6,
    };

    inline static const char* cTitle[] {
            "Halo1",
            "Halo2",
            "Halo3",
            "Halo4",
            "Groundhog",
            "Halo3ODST",
            "HaloReach"
    };

    eTitle title;
    __int32 errorCode; // 0 == ERROR_SUCCESS; 126 = ERROR_MOD_NOT_FOUND
    __int64 hModule;
    __int64 p_CreateDataAccess;
    __int64 p_ppCxxFrameHandler3;
};

struct ModuleSet {
    ModuleInfo modules[7];
};

namespace MCCHook {
    using Callback_t = void(*)(ModuleInfo*);

    bool Initialize(Callback_t load_callback, Callback_t unload_callback);
    void Shutdown();
}

#endif //ALPHA_RING_MCC_H

#ifndef MCC_MODULE_DEFINITION_H
#define MCC_MODULE_DEFINITION_H

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

#endif //MCC_MODULE_DEFINITION_H

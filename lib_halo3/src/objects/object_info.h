#ifndef ALPHA_RING_OBJECTINFO_H
#define ALPHA_RING_OBJECTINFO_H


struct ObjectInfo {
    __int64 v0;
    __int64 v1;
    __int64 address;

    inline bool IsValid() { return address; }
};


#endif //ALPHA_RING_OBJECTINFO_H

#ifndef ALPHA_RING_ENTITY_MANAGER_H
#define ALPHA_RING_ENTITY_MANAGER_H

#include "../base/base.h"

template<typename Entity>
class EntityManager {
public:
    bool setRoot(__int64 root);
    INDEX getAbsoluteIndex(Index index);
    Entity* getEntity(Index index);

    //1.3073.0
    enum class EntityOffset : __int64 {
        ACTOR = 0x8,
        PLAYER = 0x10,
        PATCHEDRESOURCEDATA = 0x20,
        OBJECT = 0x38,
        ACTORLOOP = 0x30,
        PLAYERACTION = 0x40,
        MAP = 0x48,
        SPEED = 0xC8, // 0x8 1.0/tick 0xC current tick 0x10 speed(float 1.0)
        INFO = 0x110, // input,player INDEX ... local player
        PHYSICS = 0x130, // Gravity ...
        CAMERA = 0x188,
        RENDER = 0x220, // Chud Light
        CINEMATIC = 0x450
    };

    inline __int32 entitySize(){return m_entitySize;};
    inline __int32 length(){return m_count = *(__int32*)(m_root + 0x3C);};
    inline __int64 begin(){return m_begin;}

private:
    __int64 m_root;
    __int64 m_begin;
    __int32 m_count;
    __int32 m_entitySize;
};


#endif //ALPHA_RING_ENTITY_MANAGER_H

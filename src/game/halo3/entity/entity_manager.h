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
    inline __int64 getRoot() {return m_root;}

private:
    __int64 m_root;
    __int64 m_begin;
    __int32 m_count;
    __int32 m_entitySize;
};


template<typename Entity>
bool EntityManager<Entity>::setRoot(__int64 root) {
    if (root == 0) return false;
    m_root = root;
    m_entitySize = *(__int32*)(m_root + 0x24);
    m_count = *(__int32*)(m_root + 0x3C);
    m_begin = *(__int64*)(m_root + 0x48);
    return true;
}

template<typename Entity>
INDEX EntityManager<Entity>::getAbsoluteIndex(Index index) {
    __int32 prefix;

    prefix = 0;
    index = (__int16)index;

    if (!m_begin) return NONE;

    prefix = (__int16)(m_begin + index * m_entitySize);
    return (prefix<<16)|index; // Instance Absolute INDEX
}

template<typename Entity>
Entity *EntityManager<Entity>::getEntity(Index index) {
    return (Entity*)(m_begin + (__int64)m_entitySize * (__int16)index);
}


#endif //ALPHA_RING_ENTITY_MANAGER_H

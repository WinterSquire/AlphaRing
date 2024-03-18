#ifndef ALPHA_RING_ENTITYMANAGER_H
#define ALPHA_RING_ENTITYMANAGER_H

#include "../base/base.h"

template<typename Entity>
class EntityManager {
public:
    bool update(__int64 root);
    inline __int32 entitySize(){return m_entitySize;};
    inline __int32 length(){return m_count = *(__int32*)(m_root + 0x3C);};
    inline __int64 begin(){return m_begin;}
    INDEX GetAbsoluteINDEX(Index index);
    inline Entity* operator[](Index index) {return (Entity*)(m_begin + (__int64)m_entitySize * (__int16)index);}

private:
    __int64 m_root;
    __int64 m_begin;
    __int32 m_count;
    __int32 m_entitySize;
};


template<class Entity>
INDEX EntityManager<Entity>::GetAbsoluteINDEX(Index index) {
    __int32 prefix;

    prefix = 0;
    index = (__int16)index;

    if (!m_begin) return NONE;

    prefix = (__int16)(m_begin + index * m_entitySize);
    return (prefix<<16)|index; // Instance Absolute INDEX
}

template<class Entity>
bool EntityManager<Entity>::update(__int64 root) {
    m_root = root;
    m_entitySize = *(__int32*)(m_root + 0x24);
    m_count = *(__int32*)(m_root + 0x3C);
    m_begin = *(__int64*)(m_root + 0x48);
    return true;
}

#endif //ALPHA_RING_ENTITYMANAGER_H

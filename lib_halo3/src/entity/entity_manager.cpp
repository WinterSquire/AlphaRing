#include "entity_manager.h"

template<typename Entity>
bool EntityManager<Entity>::setRoot(__int64 root) {
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

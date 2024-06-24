#pragma once

#define NONE -1
#define MAX_LOCAL_PLAYERS 4
#define MAX_ONLINE_PLAYERS 16

typedef unsigned short Index;
typedef unsigned int INDEX;
typedef unsigned int t_Player;
typedef unsigned int Datum;
typedef unsigned int StringID;

namespace Halo3ODST {
    template<typename T>
    struct entity_manager_t {
        char m_name[0x20];  // 0x0
        __int32 m_max;      // 0x20
        __int32 m_sizeof;   // 0x24
        __int32 m_un1[5];   // 0x28
        __int32 m_capacity; // 0x3C
        __int32 m_size;     // 0x40
        __int32 m_un2;      // 0x44
        __int64 m_data;     // 0x48

        inline bool isValid(__int16 index) const { return index >= 0 && index < m_size && index < m_max; }
        inline T* get(__int16 index) const { return (T*)(m_data + (__int64)m_sizeof * (__int16)index); }
        inline __int32 INDEX(__int16 index) const { return ((__int32)(*(__int16*)(m_data + index * m_sizeof)) << 16) | index;}
    };

}

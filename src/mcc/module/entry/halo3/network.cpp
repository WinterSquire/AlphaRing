#include "halo3.h"

namespace Halo3::Entry::Network {
    struct network_layer {
        //0x30
    };

    // size::0x28
    struct simulation_world {
        struct queue {
            int type; // 0x0
            queue* next; // 0x8
        };
        bool enable; // 0x0
        int count; // 0x4
        int mem_size; // 0x8
        int queue_count; // 0xC
        int queue_size; // 0x10
        queue* head; // 0x18
        queue* tail; // 0x20
    };

//    Halo3Entry(entry, 0x3B198, void**, detour, simulation_world* world) {
//        ((detour_t)entry.m_pOriginal)(world);
//    }
}
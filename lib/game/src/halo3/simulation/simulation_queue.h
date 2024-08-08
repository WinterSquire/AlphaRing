#pragma once

struct simulation_queue_definition {
    struct item {
        int type; // 0x0
        item* next; // 0x8
    };
    bool enable; // 0x0
    char padding[3];
    int count; // 0x4
    int mem_size; // 0x8
    int queue_count; // 0xC
    int queue_size; // 0x10
    int un;
    item* head; // 0x18
    item* tail; // 0x20
};

static_assert(sizeof(simulation_queue_definition) == 40);
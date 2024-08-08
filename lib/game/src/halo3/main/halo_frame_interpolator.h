#pragma once

struct halo_interpolation_definition {
    char current_frame;
    char last_frame;
    char padding[2];
    float left_over_ticks; // from game_time_globals
};

struct frame_data_intermediate_definition {
    bool enabled;
    char padding[3];
    struct S1 {
        char buffer[13324];
    } s1[2048];
    struct S2 {
        char buffer[40];
    } s2[400];
    struct S3 {
        int un;
        struct S1 {
            char buffer[13268];
        } s1[2];
    } s3[4];
    struct S4 {
        char buffer[448];
    } s4;
};

static_assert(sizeof(frame_data_intermediate_definition) == 27410164);

struct frame_data_storage_definition {
    frame_data_intermediate_definition frame_data[4];
};

static_assert(sizeof(frame_data_storage_definition) == 109640656);
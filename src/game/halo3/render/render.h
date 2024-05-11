#ifndef ALPHA_RING_RENDER_H
#define ALPHA_RING_RENDER_H

#include "../base/base.h"

struct chud_flag_t;
struct render_flag_t;
struct wireframe_flag_t;
struct chud_t;

class ICRender {
public:
    virtual inline chud_flag_t* getChudFlag() = 0;
    virtual inline render_flag_t* getRender() = 0;
    virtual inline wireframe_flag_t* getWireframe() = 0;
    virtual inline chud_t* getChud() = 0;

};

struct wireframe_flag_t {
    bool model;
    bool structure;
};

struct render_flag_t {
    bool motion_blur;
    bool atmosphere_fog;
    bool patchy_fog;
    bool render_weather;
    bool cinematic_motion_blur;
};

// size: 0x28C8i64
struct chud_t {
    struct player_chud_t {
        char un0[0x6c];
        bool chud_texture_cam; // offset: 0x6C
        char un1;
        bool cinematic_scripting_destroy_cortana_effect_cinematic; // offset: 0x6E
        char un2[0x1F8C - 0x6F];
        // offset: 0x1F8Ci64 size: ?
        struct msg_t {
            // offset: 0x90 size: 0xE8i64
            struct str_t {
                wchar_t text[0x60]; // 0x0
                int un0 = 0x100; // 0xC0
                int game_time = 0x100; // 0xC4
                int un1; // 0xC8
                int un2 = 0; // 0xCC
                int un4[5]; // 0xD0
                int un3 = 2; // 0xE4
            } str[6];
        } msg;
        char un3[0x28C8 - (0x1F8C + sizeof(msg_t))];
    } player[MAX_LOCAL_PLAYERS];
};

struct chud_flag_t {
    bool chud_show;
    bool weapon_stats;
    bool crosshair;
    bool shield;
    bool grenades;
    bool messages;
    bool motion_sensor;
    bool spike_grenades;
    bool fire_grenades;
};


#endif //ALPHA_RING_RENDER_H

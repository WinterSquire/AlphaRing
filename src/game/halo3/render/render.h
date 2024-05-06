#ifndef ALPHA_RING_RENDER_H
#define ALPHA_RING_RENDER_H

struct chud_flag_t;
struct render_flag_t;
struct wireframe_flag_t;

class ICRender {
public:
    virtual inline chud_flag_t* getChud() = 0;
    virtual inline render_flag_t* getRender() = 0;
    virtual inline wireframe_flag_t* getWireframe() = 0;

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

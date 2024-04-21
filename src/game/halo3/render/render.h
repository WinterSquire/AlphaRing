#ifndef ALPHA_RING_RENDER_H
#define ALPHA_RING_RENDER_H

struct render_flags_t;

class ICRender {
public:
    virtual inline render_flags_t* getRenderFlags() = 0;

};

extern ICRender* g_pICRender;
inline ICRender* Render() {return g_pICRender;}

struct render_flags_t {
    bool show_chud;
    bool show_weapon;
    bool show_aim;
    bool show_shield;
    bool show_grenades;
    bool show_un;
    bool show_map;
    bool show_grenade3;
    bool show_grenade4;
};


#endif //ALPHA_RING_RENDER_H

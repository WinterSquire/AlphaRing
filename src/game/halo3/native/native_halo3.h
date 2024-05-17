#ifndef ALPHA_RING_NATIVE_HALO3_H
#define ALPHA_RING_NATIVE_HALO3_H

#include "game/ICNative.h"

#include "offset_halo3.h"
#include "./native_func.h"

#include "../game/players.h"
#include "../game/game_time.h"
#include "../camera/camera.h"
#include "../objects/objects.h"
#include "../render/render.h"
#include "../input/input.h"
#include "../game/map.h"
#include "../ai/actors.h"
#include "../tag_files/tag_files.h"
#include "../physics/physics.h"

extern ICNativeFunc* g_pICHalo3NativeFunc;

extern ICRender* g_pHalo3ICRender;
extern ICH3Input* g_pHalo3ICInput;
extern ICPlayers* g_pHalo3ICPlayers;
extern ICMap* g_pHalo3ICMap;
extern ICTime* g_pHalo3ICTime;
extern ICCamera* g_pHalo3ICCamera;
extern ICActor* g_pHalo3ICActor;
extern ICObjects* g_pHalo3ICObjects;
extern ICTagFiles* g_pHalo3ICTagFiles;
extern ICPhysics* g_pHalo3ICPhysics;

class ICHalo3 : public ICNative {
public:
    inline ICNativeFunc* NativeFunc() {return g_pICHalo3NativeFunc;}
    inline ICRender* Render() {return g_pHalo3ICRender;}
    inline ICH3Input* Input() {return g_pHalo3ICInput;}
    inline ICPlayers* Players() {return g_pHalo3ICPlayers;};
    inline ICMap* Map() {return g_pHalo3ICMap;}
    inline ICTime* Time() {return g_pHalo3ICTime;}
    inline ICCamera* Camera() {return g_pHalo3ICCamera;}
    inline ICActor* Actor() {return g_pHalo3ICActor;}
    inline ICObjects* Objects() {return g_pHalo3ICObjects;}
    inline ICTagFiles* TagFiles() {return g_pHalo3ICTagFiles;}
    inline ICPhysics* Physics() {return g_pHalo3ICPhysics;}

};

extern ICHalo3* g_pICHalo3;
inline ICHalo3* NativeHalo3() {return g_pICHalo3;}


#endif //ALPHA_RING_NATIVE_HALO3_H

#pragma once

#include "../../base/base.h"

struct chud_persistent_user_data2_definition {
    char buffer[0x144];
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
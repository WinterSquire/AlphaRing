#pragma once

#pragma pack(push, 1)

struct c_player_trait_shield_vitality {
    char player_trait_damage_resistance;
    char player_trait_shield_recharge_rate;
    char player_trait_vampirism;
    char player_traits_headshot_immunity;
    char player_trait_shield_multiplier;
    char padding[3];
};

struct c_player_trait_weapons {
    __int16 player_trait_damage_modifier;
    char player_trait_initial_primary_weapon;
    char player_trait_initial_secondary_weapon;
    char player_trait_initial_grenade_count;
    char player_traits_infinite_ammo_setting;
    char player_traits_recharging_grenades;
    char player_traits_weapon_pickup_allowed;
};

struct c_player_trait_movement {
    char player_traits_movement_speed;
    char player_traits_movement_gravity;
    char player_traits_movement_vehicle_usage;
    char padding;
};

struct c_player_trait_appearance {
    char player_traits_appearance_active_camo;
    char player_traits_appearance_waypoint;
    char player_traits_appearance_aura;
    char player_traits_appearance_forced_change_color;
};

struct c_player_trait_sensors {
    __int16 player_traits_sensors_motion_tracker;
    __int16 player_traits_sensors_motion_tracker_range;
};

struct c_player_traits {
    c_player_trait_shield_vitality shield_vitality;
    c_player_trait_weapons weapons;
    c_player_trait_movement movement;
    c_player_trait_appearance appearance;
    c_player_trait_sensors sensors;
};

static_assert(sizeof(c_player_traits) == 28);

#pragma pack(pop)
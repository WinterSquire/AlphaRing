#pragma once

struct c_player_appearance {
    bool female_voice;
    char primary_color;
    char secondary_color;
    char tertiary_color;
    bool player_model_choice;

    char un;

    char foreground_emblem;
    char background_emblem;
    char emblem_flags;
    char emblem_primary_color;
    char emblem_secondary_color;
    char emblem_background_color;

    __int16 un2;

    struct model_area {
        char spartan_model_area0;
        char spartan_model_area1;
        char spartan_model_area2;
        char spartan_model_area3;

        char elite_model_area0;
        char elite_model_area1;
        char elite_model_area2;
        char elite_model_area3;
    } areas[2];

    wchar_t service_tag[4]; // 30
    char skin_assault_rifle;
    char skin_battle_rifle;
    char skin_needler;
    char skin_magnum_pistol;
    char skin_plasma_pistol;
    char skin_plasma_rifle;
    char skin_rocket_launcher;
    char skin_shotgun;
    char skin_sniper_rifle;
    char skin_flamethrower;
    char skin_fuel_rod_cannon;
    char skin_smg;
    char skin_carbine;
    char skin_energy_blade;
    char skin_visor;
    char skin_warthog;
    char skin_warthog_gauss;
    char skin_ghost;
    char skin_scorpion;
    char skin_banshee;
    char skin_hornet;
    char skin_mongoose;
    int pose;
};

static_assert(sizeof(c_player_appearance) == 64);

struct c_player_configuration {
    struct client {
        wchar_t player_name[16];
        c_player_appearance player_appearance;
        __int64 player_xuid;
        bool is_controller_attached;
        char player_last_team;
        char player_is_griefer;
        char preferred_input_device;
        int cheat_flags;
        int ban_flags;
        int button_preset;
    };

    struct host {
        wchar_t player_name[0x10];
        int player_team;
        int player_assigned_team;
    };

    client client;
    host host;

    static_assert(sizeof(client) == 120);
    static_assert(sizeof(host) == 40);
};

static_assert(sizeof(c_player_configuration) == 160);
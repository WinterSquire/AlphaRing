#pragma once

#define MAX_NAME_LENGTH 1024

struct TSettings {
    struct input_setting_t {
        bool override_input = false;
        bool enable_km = true;
        int controller_map[4] {3, 0, 1, 2};
    };

    struct profile_setting {
        profile_setting();

        bool b_override;
        bool b_override_player0;
        bool b_use_player0_profile;
        int player_count;
        struct profile_t {
            __int64 xuid;
            __int64 id;
            wchar_t name[MAX_NAME_LENGTH];
        } profiles[4];
    };

    input_setting_t input_setting;
    profile_setting profile_setting;
};

extern TSettings g_settings;
inline TSettings* Settings() { return &g_settings; }

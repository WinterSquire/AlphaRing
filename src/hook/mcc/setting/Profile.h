#pragma once

#define MAX_NAME_LENGTH 1024

struct profile_setting {
    bool b_override;
    bool b_override_player0;
    int player_count;
    struct profile_t {
        __int64 id;
        wchar_t name[MAX_NAME_LENGTH];
    } profiles[4];

    profile_setting();
};

extern profile_setting g_profile_setting;
inline profile_setting* ProfileSetting() {return &g_profile_setting;};
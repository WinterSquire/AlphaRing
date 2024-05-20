#pragma once

#define MAX_NAME_LENGTH 0x10

struct profile_setting {
    bool b_override = false;
    int player_count = 1;
    struct profile_t {
        wchar_t name[MAX_NAME_LENGTH] {L"UWU"};
    } profiles[4];
};

extern profile_setting g_profile_setting;
inline profile_setting* ProfileSetting() {return &g_profile_setting;};
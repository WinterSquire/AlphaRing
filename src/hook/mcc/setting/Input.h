#pragma once

#include <windows.h>
#include <xinput.h>

inline static const char key_map_list[] = {
        '\x1B', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '\xC0',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '\xBD', '\xBB',
        '8', '9', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        '\xDB', '\xDD', '\xDC', '\x14',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        '\xBA', '\xDE', '\x0D', '\xA0',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',
        '\xBC', '\xBE', '\xBF', '\xA1', '\xA2',
        '[', '\xA4', ' ', '\xA5', '\\', ']', '\xA3',
        '&', '(', '%', '\'', '-', '$', '!', '.', '#', '"',
        '\x90', 'o', 'j', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'm', 'k', '\x0D', 'n',
        '\x00', '\x00', '\x00', '\x00'
};

struct INPUT_t {
    void** pp_method_table;
    struct InputDevice {
        struct method_table_t {
            char un[0x38];
            __int64 (__fastcall *set_state)(InputDevice*, float, void*);
            void (__fastcall *check)(InputDevice*);
        } *p_method_table;
        char un0[2040];
        bool enable_mouse;
        char un[0x7];
        int input_user;// 0x808
        char un1[0x110];
        XINPUT_STATE state; // 0x91C
    } *p_input_device[5];
    char buffer[0x90];
    HWND hwnd; // 0xC0
    LARGE_INTEGER qpc; // 0xC8
};

// 0x130
struct input_data_t {
    int un;
    bool keyState[sizeof(key_map_list)]; // 0x4
    char buffer[0x94];
    struct mouse_t {
        float mouse_delta_x;//0x104
        float mouse_delta_y;//0x108
        float pos_x; // 0x10C
        float pos_y; // 0x110
        float un1; // 0x114
        float constant_1; // 0x118
    } mouse;
};

struct input_setting_t {
    bool override_input;
    bool enable_km = true;
    int controller_map[4] {3, 0, 1, 2};
};

extern input_setting_t g_inputSetting;
inline input_setting_t* InputSetting() {return &g_inputSetting;};

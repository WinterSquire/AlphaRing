#pragma once

#include <Windows.h>
#include <Xinput.h>

struct CInputDevice {
public:
    struct method_table_t {
        char un[0x38];
        __int64 (__fastcall *set_state)(CInputDevice*, float, void*);
        void (__fastcall *check)(CInputDevice*);
    };
public:
    method_table_t* p_method_table;
    char un0[2040];
    bool enable_mouse;
    char un[0x7];
    int input_user;// 0x808
    char un1[0x110];
    XINPUT_STATE state; // 0x91C
};
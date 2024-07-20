#pragma once

#include "CDeviceManager.h"
#include "CUserProfile.h"

struct CGameManager {
public:
    static bool Initialize(CGameManager* mng);
    static void __fastcall set_vibration(CGameManager* self, DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);
    static CUserProfile* __fastcall get_player_profile(CGameManager* self, __int64 xid);
    static char __fastcall get_xbox_user_id(CGameManager* self, __int64* pId, wchar_t *pName, int size, int index);
    static bool __fastcall get_key_state(CGameManager* self, DWORD index, input_data_t* p_input);
    static __int64 __fastcall retrive_gamepad_mapping(CGameManager* self, __int64 xid);

public:
    struct NetworkDataHeader {
        int data_size;
        int type;
        // ... data
    };

    struct FunctionTable {
        char pad0[0x110];

        // 0x110i64 get_player_profile
        CUserProfile* (__fastcall* get_player_profile)(CGameManager* self, __int64 xid);

        char pad1[0x8];

        // 0x120i64 input_get_status
        bool (__fastcall* get_key_state)(CGameManager* self, DWORD index, input_data_t* p_input);

        char pad3[0x10];

        //0x138i64 set virbation
        void (__fastcall* set_vibration)(CGameManager* self, DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);

        char (__fastcall* un_set_info)(CGameManager* self, wchar_t *a2, __int64 a3);
        __int64 (__fastcall* network_send)(CGameManager* self, __int64 network_id, NetworkDataHeader* data, unsigned int size, int type);
        __int64 (__fastcall* network_send_direct)(CGameManager* self, __int64 network_id, NetworkDataHeader* data, unsigned int size, int type);

        // 0x158 network_recv
        __int64 (__fastcall* network_recv)(CGameManager* self, char* buffer, int len, __int64* network_id, __int64* un);

        char pad4[0x160];

        // 0x2C0i64 get_xbox_user_id
        bool (__fastcall* get_xbox_user_id)(CGameManager* self, __int64* pId, wchar_t* pName, int size, int index);

        char pad5[0xD8];

        // 0x3A0i64 retrieve gamepad mapping
        __int64 (__fastcall* retrive_gamepad_mapping)(CGameManager* self,  __int64 xid);
    };

    static FunctionTable ppOriginal;
    FunctionTable* table;
};

extern CGameManager* pGameManager;
inline CGameManager* GameManager() { return pGameManager; }

#pragma once

#include "Cell.h"
#include "CUserProfile.h"
#include "CDeviceManager.h"
#include "CGamepadMapping.h"

#include "CGameEngine.h"

    struct CGameManager {
    public:
        struct Profile_t {
            __int64 id;
            int controller_index;
            wchar_t name[1024];
            CGamepadMapping mapping;
            CUserProfile profile;
        };

        struct NetworkDataHeader {
            int data_size;
            int type;
            // ... data
        };

        enum eState {
            Exit = 5,
            Exiting = 10,
        };

    public:
        static bool Initialize(CGameManager* mng);
        static __int64 get_xuid(int index);
        static int get_index(__int64 xuid);
        static Profile_t* get_profile(int index);
        static CInputDevice* get_controller(int index);

    private:
        static void __fastcall set_vibration(CGameManager* self, DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);
        static CUserProfile* __fastcall get_player_profile(CGameManager* self, __int64 xid);
        static bool __fastcall get_xbox_user_id(CGameManager* self, __int64* pId, wchar_t *pName, int size, int index);
        static bool __fastcall get_key_state(CGameManager* self, DWORD index, input_data_t* p_input);
        static CGamepadMapping* __fastcall retrive_gamepad_mapping(CGameManager* self, __int64 xid);

        static void __fastcall set_state(CGameManager* self, eState state);
        static void* __fastcall game_restart(CGameManager* self, int type, const char* reason);
        static char __fastcall game_setup(CGameManager* self, void* a2);

    public:
        struct FunctionTable {
            void* (* get_pointer)(CGameManager* self);
            __int64 (__fastcall* unknown)(CGameManager* self, LARGE_INTEGER a2, int *a3);
            int (__fastcall* ResizeCompletedEvent)(CGameManager* self);
            void (__fastcall* set_state)(CGameManager* self, eState state);
            void* (__fastcall* game_restart)(CGameManager* self, int type, const char* reason);
            void (__fastcall* game_save)(CGameManager* self, CGameEngine::Item::Data* data, CGameEngine::eEventType type);

            // 0x50 Microsoft::Xbox::Telemetry::CELL* (__fastcall* Cell)();

            char pad0[0xD0];

            // 0x100
            char (__fastcall* game_setup)(CGameManager* self, void* a2);
            __int64 (__fastcall* sub_1401E78FC)(CGameManager* self, void* a2);
            CUserProfile* (__fastcall* get_player_profile)(CGameManager* self, __int64 xid); // 0x110

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
            CGamepadMapping* (__fastcall* retrive_gamepad_mapping)(CGameManager* self,  __int64 xid);
        };

        static FunctionTable ppOriginal;

        FunctionTable* table;
        Microsoft::Xbox::Telemetry::CELL* cell;
    };

extern CGameManager* pGameManager;
inline CGameManager* GameManager() { return pGameManager; }

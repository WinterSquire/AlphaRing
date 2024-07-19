#pragma once

#define DefGlobal(name) \
    struct name##_t;    \
    extern name##_t s_##name; \
    inline name##_t* name() {return &s_##name;} \
    struct name##_t

#define ImplGlobal(name) \
    name##_t s_##name;

namespace AlphaRing::Global {
    DefGlobal(Global) {
        bool wireframe;
        bool wireframe_model;
        bool wireframe_structure;
        bool show_imgui = true;
        // on menu
        bool show_imgui_mouse = true;
        bool pause_game_on_menu_shown = false;
        bool disable_input_on_menu_shown = true;
    };

    namespace Halo3 {
        DefGlobal(Physics) {
            bool enable_bump_possession;
        };

        DefGlobal(Render) {
            bool model;
            bool structure;
        };
    }

    namespace MCC {
        DefGlobal(Profile) {
            bool b_override;
            int player_count;

            // player 0
            bool b_player0_use_km;
            bool b_override_player0;
            bool b_use_player0_profile;

            struct profile_t {
                int controller_index;
                __int64 xuid;
                __int64 id;
                wchar_t name[1024];
                __int8 gamepad_mapping[66];
            } profiles[4];

            Profile_t();

            __int64 get_xuid(int index) const {
                if (!index && !b_override_player0)
                    return profiles[0].xuid;
                if (!b_override || index >= player_count)
                    return 0;
                return profiles[index].id;
            }

            int get_index(__int64 xuid) const {
                for (int i = 0; i < 4; ++i)
                    if (xuid == profiles[i].id)
                        return i;
                return 0;
            }

            inline int get_controller_index(int index) const {return profiles[index].controller_index;}
            static const char** get_action_names();
            static const char** get_button_names();
        };
    }
}
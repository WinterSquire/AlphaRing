#include "halo3.h"

#include <vector>
#include <mutex>
#include <imgui.h>

namespace Halo3::Entry::Simulation {
    struct simulation {
        char buffer[2200];
        struct queue {
            struct item {
                int type; // 0x0
                item* next; // 0x8
            };
            bool enable; // 0x0
            int count; // 0x4
            int mem_size; // 0x8
            int queue_count; // 0xC
            int queue_size; // 0x10
            item* head; // 0x18
            item* tail; // 0x20
        } queue1, queue2;
        __int64 players_bit;
        int object_INDEX[16];
        struct ControlData {
            const static int k_maximum_weapons_per_unit = 4;
            const static int k_unit_grenade_types_count = 4;
            const static __int16 k_unit_aiming_speeds_count = 0x8000;

            int un;
            __int16 aiming_speed;
            __int16 un2;
            char weapon_indices[2];
            __int16 grenade_index;
            __int16 zoom_level;
            char buffer[10];
            struct Throttle {
                float i,j,k;
            } throttle; // 24 movement
            float primary_trigger;
            float secondary_trigger;
            Vector3 facing_vector;
            Vector3 aiming_vector;
            Vector3 looking_vector;
            Vector3 gaze_position;
            struct AimAssist {
                char buffer[36];
            } aim_assist_data;
        } control_data[10];
        char buffer2[2144];
    };

    static_assert(sizeof(simulation) == 5776);

    static std::mutex g_mutex;
    static bool bCapture = false;
    static bool bPlayback = false;
    static int playback_tick = 0;
    static std::vector<simulation::ControlData> simulations;

    Halo3Entry(entry, 0x350B24, char, detour, unsigned __int16 unit, simulation::ControlData* control_data) {
        if (bCapture) {
            std::lock_guard<std::mutex> g_lock(g_mutex);
            simulations.push_back(*control_data);
        } else if (bPlayback) {
            std::lock_guard<std::mutex> g_lock(g_mutex);
            if (playback_tick < simulations.size()) {
                memcpy(control_data, &simulations[playback_tick], sizeof(simulation::ControlData));
                playback_tick++;
            } else {
                bPlayback = false;
            }
        }
        auto result = ((detour_t)entry.m_pOriginal)(unit, control_data);
        return result;
    }

    void ImGuiContext() {
        std::lock_guard<std::mutex> g_lock(g_mutex);

        auto status = "Idle";

        if (bCapture) status = "Capture";
        else if (bPlayback) status = "Playback";

        ImGui::Text("Simulation Status: %s", status);

        int value = playback_tick;
        if (ImGui::InputInt("Tick", &value) && (!value || (value > 0 && value < simulations.size()))) {
            playback_tick = value;
        }

        if (ImGui::Button("Capture")) {
            bCapture = true;
            bPlayback = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause##0")) {
            bCapture = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume##0")) {
            bCapture = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            simulations.clear();
            playback_tick = 0;
        }

        if (ImGui::Button("Replay")) {
            bPlayback = true;
            bCapture = false;
            playback_tick = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause##1")) {
            bPlayback = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume##1")) {
            bPlayback = true;
        }
    }
}

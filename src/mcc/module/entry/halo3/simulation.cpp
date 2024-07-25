#include "halo3.h"

#include "common.h"

#include <vector>
#include <mutex>
#include <imgui.h>

namespace Halo3::Entry::Simulation {
    static std::mutex g_mutex1;
    bool bTAS = false;
    bool bRun = false;
    int run_tick = 0;

    Halo3Entry(entry1, 0xEEC5C, __int64, detour1, int tick, float* a2) {
        {
            std::lock_guard<std::mutex> g_lock(g_mutex1);
            if (bTAS) {
                tick = 0;
                if (bRun) {
                    tick = run_tick;
                    bRun = false;
                }
            }
        }
        return ((detour1_t)entry1.m_pOriginal)(tick, a2);
    }

    void ImGuiContext1() {
        std::lock_guard<std::mutex> g_lock(g_mutex1);

        ImGui::PushItemWidth(200.0f);
        ImGui::Checkbox("TAS", &bTAS);

        if (!bTAS) {
            ImGui::PopItemWidth();
            return;
        }

        ImGui::SameLine();

        int value = run_tick;
        if (ImGui::InputInt("Tick", &value) && value >= 0) {
            run_tick = value;
        }
        ImGui::PopItemWidth();

        ImGui::SameLine();

        if (ImGui::Button("Run")) {
            bRun = true;
        }
    }
}

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

            void ImGuiContext() {
                int value;

                value = aiming_speed;
                if (ImGui::InputInt("Aiming Speed", &value) && value >= 0 && value < k_unit_aiming_speeds_count) {
                    aiming_speed = value;
                }

                value = weapon_indices[0];
                if (ImGui::InputInt("Weapon Index 1", &value) && value >= 0 && value < k_maximum_weapons_per_unit) {
                    weapon_indices[0] = value;
                }

                value = weapon_indices[1];
                if (ImGui::InputInt("Weapon Index 2", &value) && value >= 0 && value < k_maximum_weapons_per_unit) {
                    weapon_indices[1] = value;
                }

                value = grenade_index;
                if (ImGui::InputInt("Grenade Index", &value) && value >= 0 && value < k_unit_grenade_types_count) {
                    grenade_index = value;
                }

                value = zoom_level;
                if (ImGui::InputInt("Zoom Level", &value) && value >= 0 && value < 0xFFFF) {
                    zoom_level = value;
                }

                ImGui::DragFloat3("Throttle(Movement?)", &throttle.i, 0.01f, -1.0f, 1.0f);

                ImGui::DragFloat("Primary Trigger", &primary_trigger, 0.01f);
                ImGui::DragFloat("Secondary Trigger", &secondary_trigger, 0.01f);

                ImGui::DragFloat3("Facing Vector", &facing_vector.x, 0.01f);
                ImGui::DragFloat3("Aiming Vector", &aiming_vector.x, 0.01f);
                ImGui::DragFloat3("Looking Vector", &looking_vector.x, 0.01f);
                ImGui::DragFloat3("Gaze Position", &gaze_position.x, 0.01f);

            }
        } control_data[10];
        char buffer2[2144];
    };

    static std::mutex g_mutex;

    static_assert(sizeof(simulation) == 5776);

    static bool bCapture = false;
    static bool bPlayback = false;
    static int playback_tick = 0;
    static int total_tick = 0;
    static struct Node {
        simulation::ControlData data;
        Node* next;
        Node* prev;
    } *current, *head, *tail;

    Halo3Entry(entry, 0x350B24, char, detour, unsigned __int16 unit, simulation::ControlData* control_data) {
        if (bCapture) {
            // create new node
            auto node = new Node();
            node->next = node->prev = nullptr;
            memcpy(&node->data, control_data, sizeof(simulation::ControlData));

            // insert new node
            {
                std::lock_guard<std::mutex> g_lock(g_mutex);
                if (head == nullptr) head = node;
                if (tail != nullptr) {
                    tail->next = node;
                    node->prev = tail;
                }
                tail = node;
                ++total_tick;
            }
        } else if (bPlayback) {
            std::lock_guard<std::mutex> g_lock(g_mutex);
            if (current != nullptr) {
                memcpy(control_data, &current->data, sizeof(simulation::ControlData));
                playback_tick++;
                if (current->next != nullptr) {
                    current = current->next;
                } else {
                    bPlayback = false;
                }
            } else {
                bPlayback = false;
            }
        }
        return ((detour_t)entry.m_pOriginal)(unit, control_data);
    }

    void ImGuiContext() {
        if (ImGui::CollapsingHeader("Simulation") == false) return;

        std::lock_guard<std::mutex> g_lock(g_mutex);

        auto status = "Idle";
        if (bCapture) status = "Capture";
        else if (bPlayback) status = "Playback";

        ImGui::Indent();
        ImGui::Text("Simulation Status: %s", status);

        if (ImGui::TreeNode("Control Data")) {
            if (current != nullptr)
                current->data.ImGuiContext();
            ImGui::TreePop();
        }

        ImGui::Text("Tick[%d]", total_tick);

        ImGui::SameLine();

        int value = playback_tick;
        ImGui::PushItemWidth(200.0f);
        if (ImGui::InputInt("##0", &value)) {
            if (current == nullptr) {
                current = head;
                playback_tick = 0;
            }
            if (value <= 0) {
                current = head;
                playback_tick = 0;
            } else if (value >= total_tick - 1) {
                current = tail;
                playback_tick = total_tick - 1;
            } else if (playback_tick < value) {
                while (playback_tick < value) {
                    current = current->next;
                    playback_tick++;
                    assertm(current != nullptr, "Invalid playback tick");
                }
            } else if (playback_tick > value) {
                while (playback_tick > value) {
                    current = current->prev;
                    playback_tick--;
                    assertm(current != nullptr, "Invalid playback tick");
                }
            }
        }
        ImGui::PopItemWidth();

        ImGui::SameLine();

        // duplicate new node and then insert back
        if (ImGui::Button("Duplicate") && current != nullptr) {
            auto node = new Node();
            memcpy(&node->data, &current->data, sizeof(simulation::ControlData));

            node->next = current->next;
            node->prev = current;
            if (current->next != nullptr) current->next->prev = node;
            current->next = node;

            if (current == tail)
                tail = node;
            total_tick++;
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete") && current != nullptr) {
            if (current == head) {
                head = head->next;
                if (head != nullptr) head->prev = nullptr;
            } else if (current == tail) {
                tail = tail->prev;
                if (tail != nullptr) tail->next = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            auto prev = current->prev;
            delete current;
            current = prev;
            playback_tick--;
            total_tick--;
            if (playback_tick < 0) playback_tick = 0;
            if (total_tick < 0) total_tick = 0;
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
            for (auto node = head; node != nullptr;) {
                auto next = node->next;
                delete node;
                node = next;
            }
            head = tail = current = nullptr;
            total_tick = playback_tick = 0;
            bCapture = bPlayback = false;
        }

        if (ImGui::Button("Replay")) {
            bPlayback = true;
            bCapture = false;
            current = head;
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
        ImGui::Unindent();
    }
}

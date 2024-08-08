#include "halo3.h"

#include "common.h"

#include <vector>
#include <mutex>
#include <imgui.h>

static std::mutex g_mutex1;
static bool bTAS = false;
static bool bRun = false;
static int run_tick = 0;

static std::mutex g_mutex;

static bool bCapture = false;
static bool bPlayback = false;
static int playback_tick = 0;
static int total_tick = 0;
static struct Node {
    unit_control_definition data;
    Node* next;
    Node* prev;
} *current, *head, *tail;

static void SaveFileHandler();

namespace Halo3::Entry::Simulation {
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
    Halo3Entry(entry, 0x350B24, char, detour, unsigned __int16 unit, unit_control_definition* control_data) {
        if (bCapture) {
            // create new node
            auto node = new Node();
            node->next = node->prev = nullptr;
            memcpy(&node->data, control_data, sizeof(unit_control_definition));

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
                memcpy(control_data, &current->data, sizeof(unit_control_definition));
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
            memcpy(&node->data, &current->data, sizeof(unit_control_definition));

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

        SaveFileHandler();

        ImGui::Unindent();
    }
}

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void to_json(json& j, Vector3* vector) {
    j = json::object({
        {"x", vector->x},
        {"y", vector->y},
        {"z", vector->z}
    });
}

void to_json(json& j, aim_assist_definition* assist_data) {
    j = json::object({
        {"target_player", assist_data->target_player},
        {"target_object", assist_data->target_object},
        {"model_target", assist_data->model_target},
        {"primary_autoaim_level", assist_data->primary_autoaim_level},
        {"secondary_autoaim_level", assist_data->secondary_autoaim_level},
        {"lead_vector", &assist_data->lead_vector},
        {"flags", assist_data->flags}
    });
}

void to_json(json& j, unit_control_definition* control_data) {
    j = json::object({
        {"identifier", control_data->identifier},
        {"un", control_data->un},
        {"weapon_set_identifier", control_data->weapon_set_identifier},
        {"primary_weapon_indices", control_data->primary_weapon_indices},
        {"secondary_weapon_indices", control_data->secondary_weapon_indices},
        {"grenade_index", control_data->grenade_index},
        {"zoom_level", control_data->zoom_level},
        {"interaction_type", control_data->interaction_type},
        {"action_flags", control_data->action_flags},
        {"throttle", &control_data->throttle},
        {"primary_trigger", control_data->primary_trigger},
        {"secondary_trigger", control_data->secondary_trigger},
        {"facing_vector", &control_data->facing_vector},
        {"aiming_vector", &control_data->aiming_vector},
        {"looking_vector", &control_data->looking_vector},
        {"gaze_position", &control_data->gaze_position},
        {"aim_assist_data", &control_data->aim_assist_data}
    });
}

void to_json(json& j, Node* node) {
    while (node != nullptr) {
        json j1;
        to_json(j1, &node->data);
        j.push_back(j1);
        node = node->next;
    }
}

static void SaveFileHandler() {
    static char buffer[1024] {0};
    static bool show_save_window = false;

    // save to json
    if (ImGui::Button("Save")) {
        show_save_window = true;
    }

    if (show_save_window) {
        if (ImGui::Begin("Save Control Data", &show_save_window)) {
            ImGui::Text("alpha_ring/");
            ImGui::SameLine();
            ImGui::InputText("File Name", buffer, sizeof(buffer));

            if (ImGui::Button("Save")) {
                if (head != nullptr) {
                    json j;
                    to_json(j, head);
                    auto result = j.dump(4);
                    AlphaRing::Filesystem::Save(buffer, result.c_str(), result.length());
                }
                show_save_window = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                show_save_window = false;
            }
        }
        ImGui::End();
    }
}

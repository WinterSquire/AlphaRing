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

    static std::mutex g_mutex;

    static bool bCapture = false;
    static bool bPlayback = false;
    static int playback_tick = 0;
    static int total_tick = 0;
    static struct Node {
        unit_control_definition* data;
        Node* next;
        Node* prev;
    } *current, *head, *tail;

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
        ImGui::Unindent();
    }
}

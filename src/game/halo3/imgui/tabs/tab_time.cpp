#include "tabs.h"

#include "game/halo3/game/game_time.h"

void Halo3::IMGUI::Tabs::tab_time() {
    char buffer[1024];
    auto p_time = Time()->getGameTime();
    __int16 tick_per_second = 0;
    __int32 game_time = 0;
    float speed = 0;

    if (p_time != nullptr) {
        tick_per_second = p_time->tick_per_second;
        game_time = p_time->game_time;
        speed = p_time->speed;
    }
    sprintf(buffer, "Game Time: %d\nTick Per Second: %hd\nSpeed: %.2f", game_time, tick_per_second, speed);
    ImGui::Text(buffer);
}


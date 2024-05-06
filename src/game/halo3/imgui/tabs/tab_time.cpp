#include "../basic_widget.h"
#include "game/halo3/native/native.h"

class TabTime : public BasicWidget {
public:
    TabTime(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override{}

};

static TabTime s_instance("Time");
BasicWidget* tab_time = &s_instance;

void TabTime::render() {
    char buffer[1024];
    auto p_time = NativeHalo3()->Time()->getGameTime();
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

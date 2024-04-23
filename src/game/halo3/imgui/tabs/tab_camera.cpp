#include "../basic_widget.h"

#include "game/halo3/native/native.h"

class TabCamera : public BasicWidget {
public:
    TabCamera(const char* name) : BasicWidget(name) {}
    void render() override;

private:
    int camera_mode = 0;
};

static TabCamera s_instance("Camera");
BasicWidget* tab_camera = &s_instance;

void TabCamera::render() {
    char buffer[1024];
    const char* format = R"(
Camera:
    Mode: %s
    Target: %X
    position: %.2f %.2f %.2f
)";

    auto p_camera = Camera()->getCamera();
    auto p_camera_data = Camera()->getCameraData(0);

    if (p_camera == nullptr || p_camera_data == nullptr) return;

    sprintf(buffer, format,
            eCameraModeName[p_camera->mode], p_camera->camera[0].target,
            p_camera_data->data.position.x, p_camera_data->data.position.y, p_camera_data->data.position.z
        );

    ImGui::Text(buffer);

    camera_mode = p_camera->mode;
    if (ImGui::Combo("Camera Mode", &camera_mode, eCameraModeName, sizeof(eCameraModeName) / sizeof(const char*))) {
        int mode = camera_mode;
        setState([mode] {
            NativeFunc()->player_set_camera(0, (eCameraMode)mode);
        });
    }
}

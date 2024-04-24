#include "../basic_widget.h"

#include "game/halo3/native/native.h"

// todo timeline editor
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

    auto p_video_setting = Camera()->getVideoSetting();
    if (p_video_setting) {
        ImGui::Text("Video Setting");
        ImGui::Indent();
        ImGui::SliderFloat("FOV FP", &p_video_setting->fov_fp, 0, 150);
        ImGui::SliderFloat("FOV 3rd", &p_video_setting->fov_3rd, 0, 150);
        ImGui::Unindent();
    }

    camera_mode = p_camera->mode;
    if (ImGui::Combo("Camera Mode", &camera_mode, eCameraModeName, sizeof(eCameraModeName) / sizeof(const char*))) {
        int mode = camera_mode;
        setState([mode] {
            NativeFunc()->player_set_camera(0, (eCameraMode)mode);
        });
    }

    if (p_camera->mode == CAMERAMODE_FLYING) {
        ImGui::InputFloat3("Position", &p_camera->camera[0].position.x);
        auto rotation = (Degree3)p_camera->camera[0].rotation;
        if (ImGui::SliderFloat3("Rotation", &rotation.x, 0, 360))
            p_camera->camera[0].rotation = (Radian3)rotation;
    }

}

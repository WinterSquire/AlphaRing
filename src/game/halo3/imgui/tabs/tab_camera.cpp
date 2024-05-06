#include "../basic_widget.h"

#include "game/halo3/native/native.h"
#include "imgui/curve_editor.h"

class TabCamera : public BasicWidget {
public:
    TabCamera(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override;

private:
    int camera_mode = 0;
    ImGui::CustomWidget::CurveEditor curveEditor;
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

    auto p_camera = NativeHalo3()->Camera()->getCamera();
    auto p_video_setting = NativeHalo3()->Camera()->getVideoSetting();
    auto p_camera_data = NativeHalo3()->Camera()->getCameraData(0);

    if (!p_camera || !p_camera_data || !p_video_setting) return;

    sprintf(buffer, format,
            eCameraModeName[p_camera->mode], p_camera->camera[0].target,
            p_camera_data->data.position.x, p_camera_data->data.position.y, p_camera_data->data.position.z
    );

    ImGui::Text(buffer);

    if (p_video_setting) {
        ImGui::Text("Video Setting");
        ImGui::Indent();
        ImGui::DragFloat("FOV FP", &p_video_setting->fov_fp, 1.0f, 0.0f, 150.0f);
        ImGui::DragFloat("FOV 3rd", &p_video_setting->fov_3rd, 1.0f, 0.0f, 150.0f);
        ImGui::Unindent();
    }

    camera_mode = p_camera->mode;
    if (ImGui::Combo("Camera Mode", &camera_mode, eCameraModeName, sizeof(eCameraModeName) / sizeof(const char*))) {
        int mode = camera_mode;
        setState([mode] {
            NativeHalo3()->NativeFunc()->player_set_camera(0, (eCameraMode)mode);
        });
    }

    if (p_camera->mode != CAMERAMODE_FLYING) return;
    ImGui::DragFloat3("Position", &p_camera->camera[0].position.x, 0.01f);
    auto rotation = (Degree3)p_camera->camera[0].rotation;
    if (ImGui::DragFloat3("Rotation", &rotation.x, 1.0f, -360.0f, 360.0f));
        p_camera->camera[0].rotation = (Radian3)rotation;

    ImGui::Begin("Curve Editor");
    curveEditor.render();
    ImGui::End();
}

void TabCamera::update() {
    auto p_camera = NativeHalo3()->Camera()->getCamera();

    if (!p_camera || p_camera->mode != CAMERAMODE_FLYING) return;

    auto p_game_time = NativeHalo3()->Time()->getGameTime();
    auto p_video_setting = NativeHalo3()->Camera()->getVideoSetting();

    if ( !p_video_setting || !p_game_time) return;

    auto& playing = curveEditor.playing();
    auto& frame = curveEditor.frame();

    float* const binding[] {
            &p_camera->camera[0].position.x,
            &p_camera->camera[0].position.y,
            &p_camera->camera[0].position.z,
            &p_camera->camera[0].rotation.x,
            &p_camera->camera[0].rotation.y,
            &p_camera->camera[0].rotation.z,
            &p_video_setting->fov_fp,
    };

    auto update = [&] {
        for (int i = 0; i < curveEditor.CURVE_COUNT; ++i) {
            auto& curve = curveEditor.getCurve(i);
            if (!curve.enabled) continue;
            *binding[i] = curve.getValue(frame);
        }
    };

    auto addkey = [&] {
        for (int i = 0; i < curveEditor.CURVE_COUNT; ++i) {
            auto& curve = curveEditor.getCurve(i);
            if (!curve.enabled) continue;
            curve.addKeyframe({frame, *binding[i]});
        }
    };

    if (ImGui::IsKeyPressed(ImGuiKey_Space, false)) {
        playing = !playing;
    }

    if (playing) {
        ++frame;
        update();
    } else if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) {
        --frame;
        update();
    } else if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) {
        ++frame;
        update();
    } else if (ImGui::IsKeyPressed(ImGuiKey_K, false)) {
        addkey();
    }
}

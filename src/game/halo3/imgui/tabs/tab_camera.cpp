#include "../basic_widget.h"
#include "imgui/curve_editor.h"

#include "game/halo3/native/native.h"

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
    auto p_splitScreen = NativeHalo3()->Camera()->getSplitScreen();
    auto p_video_setting = NativeHalo3()->Camera()->getVideoSetting();
    auto p_data = NativeHalo3()->Camera()->getCameraData();

    if (!p_camera || !p_data || !p_video_setting || !p_splitScreen) return;

    if (p_splitScreen) {
        ImGui::Text("Split Screen");
        ImGui::Indent();
        int v = p_splitScreen->screen_count;
        if (ImGui::InputInt("count", &v) && v >= 1 && v <= 4) p_splitScreen->screen_count = v;
        ImGui::Unindent();
    }

    if (p_video_setting) {
        ImGui::Text("Video Setting");
        ImGui::Indent();
        ImGui::DragFloat("FOV FP", &p_video_setting->fov_fp, 1.0f, 0.0f, 179.999f);
        ImGui::DragFloat("FOV 3rd", &p_video_setting->fov_3rd, 1.0f, 0.0f, 179.999f);
        ImGui::Unindent();
    }

    for (int i = 0; i < p_splitScreen->screen_count; ++i) {
        auto p_cam = &p_camera->camera[i];
        auto p_cam_data = &p_data->data[i];
        auto p_mode = &p_camera->mode[i].mode;

        ImGui::Text(format,
                    eCameraModeName[*p_mode], p_cam->target,
                    p_cam_data->data.position.x, p_cam_data->data.position.y, p_cam_data->data.position.z
        );

        ImGui::PushID(i << 2 | 0);
        if (ImGui::Combo("Camera Mode", (int*)p_mode, eCameraModeName, sizeof(eCameraModeName) / sizeof(const char*))) {
            int mode = *p_mode;
            setState([i, mode] {
                NativeHalo3()->NativeFunc()->player_set_camera(i, (eCameraMode)mode);
            });
        }
        ImGui::PopID();


        if (*p_mode == CAMERAMODE_FLYING) {
            ImGui::PushID(i << 2 | 1);
            ImGui::DragFloat3("Position", &p_cam->position.x, 0.01f);
            ImGui::PopID();

            auto rotation = (Degree3)p_cam->rotation;
            ImGui::PushID(i << 2 | 0);
            if (ImGui::DragFloat3("Rotation", &rotation.x, 1.0f, -360.0f, 360.0f))
                p_cam->rotation = (Radian3)rotation;
            ImGui::PopID();
        }
    }

    if (p_camera->mode[0].mode == CAMERAMODE_FLYING) {
        ImGui::Begin("Curve Editor");
        curveEditor.render();
        ImGui::End();
    }
}

void TabCamera::update() {
    auto p_camera = NativeHalo3()->Camera()->getCamera();

    if (!p_camera || p_camera->mode[0].mode != CAMERAMODE_FLYING) return;

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

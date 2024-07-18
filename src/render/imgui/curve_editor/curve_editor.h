#ifndef CUSTOM_WIDGET_CURVE_EDITOR_H
#define CUSTOM_WIDGET_CURVE_EDITOR_H

#include "basic_widget.h"
#include "curve.h"

namespace ImGui::CustomWidget {
    class CurveEditor : public BasicWidget {
    public:
        CurveEditor();
        void render() override;

        enum eCurve : int {
            Curve_Pos_X,
            Curve_Pos_Y,
            Curve_Pos_Z,
            Curve_Rot_X,
            Curve_Rot_Y,
            Curve_Rot_Z,
            Curve_FOV,
        };

        static const int CURVE_COUNT = 7;
        inline curve_t& getCurve(int curve) {return m_curves[curve];}
        inline float& frame() {return m_frame;}
        inline bool& playing() {return b_playing;}
    private:
        void render_left();
        void render_center();
        void render_right();

    private:
        const float RESIZE_BUTTON_WIDTH = 10.0f;
        const float NODE_SLOT_RADIUS = 10.0f;
        const ImVec2 RADIUS {NODE_SLOT_RADIUS, NODE_SLOT_RADIUS};
        const ImU32 COLOR_BLUE = IM_COL32(0, 0, 255, 255);
        const ImU32 COLOR_WITHE = IM_COL32(255, 255, 255, 255);
        const float FRAME_BAR_HEIGHT = 20.0f;
        const float ZOOM_MIN = 0.1f;
        const float ZOOM_MAX = 5.0f;
        float m_gird_x_step = 100.0f;
        float m_gird_y_step = 1.0f;

        curve_t m_curves[CURVE_COUNT] {
                {"X Position",{1.0f, 0.0f, 0.0f}},
                {"Y Position",{0.0f, 1.0f, 0.0f}},
                {"Z Position",{0.0f, 0.0f, 1.0f}},
                {"X Euler Rotation",{1.0f, 0.0f, 0.0f}},
                {"Y Euler Rotation",{0.0f, 1.0f, 0.0f}},
                {"Z Euler Rotation",{0.0f, 0.0f, 1.0f}},
                {"FOV",{1.0f, 0.0f, 0.0f}},
        };

        bool b_playing = false;

        ImVec2 m_scrolling;
        float m_zoom = 1.0f;
        float ratio_y = 100.0f;
        float m_seperator1 = 0.2f;
        float m_seperator2 = 0.6f;

        float m_frame = 0;
        int m_line = -1;
        keyframe_t* m_pKeyframe;
        int m_handle = -1;
    };
}

#endif //CUSTOM_WIDGET_CURVE_EDITOR_H

#include "curve_editor.h"

ImGui::CustomWidget::CurveEditor::CurveEditor() {
    m_scrolling = {0, 0};
}

void ImGui::CustomWidget::CurveEditor::render() {
    const auto [width, height] = ImGui::GetWindowSize();
    const auto left_width = width * m_seperator1;
    const auto center_width = width * (m_seperator2 - m_seperator1);

    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGuiIO& io = ImGui::GetIO();

    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);

    draw_list->AddRect(canvas_p0, canvas_p1, COLOR_WITHE);

    ImGui::BeginChild("Left", {left_width, 0});
    render_left();
    ImGui::EndChild();

    ImGui::SameLine();
    {
        const auto pos_x = ImGui::GetCursorScreenPos().x;
        draw_list->AddLine({pos_x, canvas_p0.y}, {pos_x, canvas_p1.y}, COLOR_WITHE);
        ImGui::SetCursorScreenPos({pos_x - RESIZE_BUTTON_WIDTH / 2, canvas_p0.y});
        ImGui::InvisibleButton("Resize1", {RESIZE_BUTTON_WIDTH, canvas_sz.y});
        if (ImGui::IsItemHovered())
            ImGui::SetMouseCursor(4);
        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)){
            ImGui::SetMouseCursor(4);
            m_seperator1 = mouse_pos_in_canvas.x / canvas_sz.x;
        }
    }
    ImGui::SameLine();

    ImGui::BeginChild("Center", {center_width, 0});
    render_center();
    ImGui::EndChild();

    ImGui::SameLine();
    {
        const auto pos_x = ImGui::GetCursorScreenPos().x;
        draw_list->AddLine({pos_x, canvas_p0.y}, {pos_x, canvas_p1.y}, COLOR_WITHE);
        ImGui::SetCursorScreenPos({pos_x - RESIZE_BUTTON_WIDTH / 2, canvas_p0.y});
        ImGui::InvisibleButton("Resize2", {RESIZE_BUTTON_WIDTH, canvas_sz.y});
        if (ImGui::IsItemHovered())
            ImGui::SetMouseCursor(4);
        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
            ImGui::SetMouseCursor(4);
            m_seperator2 = mouse_pos_in_canvas.x / canvas_sz.x;
        }
    }
    ImGui::SameLine();

    ImGui::BeginChild("Right");
    render_right();
    ImGui::EndChild();
}

void ImGui::CustomWidget::CurveEditor::render_left() {
    char buffer[1024];
    for (int i = 0; i < CURVE_COUNT; ++i) {
        const int id_prefix = i << 2;
        auto& curve = m_curves[i];
        ImGui::Text(curve.p_name);
        ImGui::SameLine();
        ImGui::PushID(id_prefix | 0);
        ImGui::Checkbox("V", &curve.visibility);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(id_prefix | 1);
        ImGui::Checkbox("E", &curve.enabled);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(id_prefix | 1);
        ImGui::Checkbox("L", &curve.locked);
        ImGui::PopID();

        sprintf(buffer, "Value: %.2f", curve.getValue(m_frame));
        ImGui::SameLine();
        ImGui::Text(buffer);
    }
}

void ImGui::CustomWidget::CurveEditor::render_center() {
    char buffer[1024];
    ImVec2 canvas_o = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
    canvas_sz.y -= FRAME_BAR_HEIGHT;
    ImVec2 canvas_p0 = {canvas_o.x, canvas_o.y + FRAME_BAR_HEIGHT};
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    const auto mouse_delta = ImVec2{io.MouseDelta.x / m_zoom, io.MouseDelta.y / m_zoom / ratio_y };
    const auto scrolling = m_scrolling * m_zoom;

    const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

    // Draw border and background color
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

    // Draw Grid
    const float GRID_X_STEP = m_gird_x_step * m_zoom;

    for (float original_value = fmodf(m_scrolling.x, m_gird_x_step), scaled_value = fmodf(scrolling.x, GRID_X_STEP);
         scaled_value < canvas_sz.x;
         scaled_value += GRID_X_STEP, original_value += m_gird_x_step)
    {
        const auto p1 = ImVec2(canvas_p0.x + scaled_value, canvas_p0.y);
        const auto p2 = ImVec2(canvas_p0.x + scaled_value, canvas_p1.y);
        sprintf(buffer, "%.0f", original_value - m_scrolling.x);
        draw_list->AddText({p1.x, p1.y - FRAME_BAR_HEIGHT}, COLOR_WITHE, buffer);
        draw_list->AddLine(p1, p2, IM_COL32(200, 200, 200, 40));
    }

    const float GRID_Y_STEP = m_gird_y_step * m_zoom * ratio_y;
    for (float original_value = fmodf(m_scrolling.y, m_gird_y_step * ratio_y), scaled_value = fmodf(scrolling.y, GRID_Y_STEP);
         scaled_value < canvas_sz.y;
         scaled_value += GRID_Y_STEP, original_value += m_gird_y_step * ratio_y)
    {
        const auto p1 = ImVec2(canvas_p0.x, canvas_p0.y + scaled_value);
        const auto p2 = ImVec2(canvas_p1.x, canvas_p0.y + scaled_value);
        sprintf(buffer, "%.0f", (original_value - m_scrolling.y) / ratio_y);
        draw_list->AddText(p1, COLOR_WITHE, buffer);
        draw_list->AddLine(p1, p2, IM_COL32(200, 200, 200, 40));
    }

    // Draw frame bar
    const auto frame_center = origin.x + m_frame * m_zoom;
    const auto frame_l = frame_center - FRAME_BAR_HEIGHT / 2;
    const auto frame_t = canvas_o.y;
    const auto frame_r = frame_center + FRAME_BAR_HEIGHT / 2;
    const auto frame_b = canvas_o.y + FRAME_BAR_HEIGHT;

    sprintf(buffer, "%.0f", m_frame);
    draw_list->AddRectFilled({frame_l, frame_t}, {frame_r, frame_b}, COLOR_BLUE);
    draw_list->AddText({frame_center, frame_t}, COLOR_WITHE, buffer);
    draw_list->AddLine({frame_center, frame_b}, {frame_center, canvas_p1.y}, COLOR_BLUE, 3.0f);

    ImGui::SetCursorScreenPos(canvas_o);
    ImGui::InvisibleButton("Frame Bar", {canvas_sz.x, FRAME_BAR_HEIGHT});
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f)) {
        if (mouse_delta.x < -0.001) m_frame -= 1;
        else if (mouse_delta.x > 0.001) m_frame += 1;
    }

    // Handle Points
    for (int k = 0; k < CURVE_COUNT; ++k) {
        auto& curve = m_curves[k];

        if (!curve.visibility) continue;

        const auto& curve_color = k == m_line ? curve.curve_selected_color : curve.curve_unselected_color;

        for (auto pKeyframe = curve.p_head; pKeyframe != nullptr; pKeyframe = pKeyframe->next) {
            const int id_prefix = pKeyframe->id << 3;

            const ImVec2 pos_point[] {
                    {origin.x + pKeyframe->left_handle.x * m_zoom, origin.y + pKeyframe->left_handle.y * m_zoom * ratio_y},
                    {origin.x + pKeyframe->keyframe.x * m_zoom, origin.y +  pKeyframe->keyframe.y * m_zoom * ratio_y},
                    {origin.x + pKeyframe->right_handle.x * m_zoom, origin.y + pKeyframe->right_handle.y * m_zoom * ratio_y}
            };

            // Draw Lines
            if (pKeyframe->prev == nullptr) {
                draw_list->AddLine({canvas_p0.x, pos_point[1].y}, {pos_point[1].x, pos_point[1].y}, curve_color, 3.0f);
            }
            if (pKeyframe->next != nullptr) {
                const ImVec2 pos_next_lh {origin.x + pKeyframe->next->left_handle.x * m_zoom, origin.y + pKeyframe->next->left_handle.y * m_zoom * ratio_y};
                const ImVec2 pos_next_ct {origin.x + pKeyframe->next->keyframe.x * m_zoom, origin.y + pKeyframe->next->keyframe.y * m_zoom * ratio_y};
                draw_list->AddBezierCubic(pos_point[1], pos_point[2], pos_next_lh, pos_next_ct, curve_color, 3.0f);
            } else {
                draw_list->AddLine({pos_point[1].x, pos_point[1].y}, {canvas_p1.x, pos_point[1].y}, curve_color, 3.0f);
            }

            // Draw Points
            auto const selected_color = IM_COL32(255, 255, 255, 255);
            auto const unselected_color = IM_COL32(0, 0, 0, 255);

            for (int j = 0; j < 3; ++j) {
                ImU32 color = unselected_color;
                const ImVec2& pos = pos_point[j];

                // clip points
                if (pos.x - NODE_SLOT_RADIUS <= canvas_p0.x || pos.y - NODE_SLOT_RADIUS <= canvas_p0.y ||
                    pos.x + NODE_SLOT_RADIUS >= canvas_p1.x || pos.y + NODE_SLOT_RADIUS >= canvas_p1.y)
                    continue;

                // draw
                if (pKeyframe == m_pKeyframe && j == m_handle) color = selected_color;
                if (j != 1) draw_list->AddLine(pos_point[1], pos, color);
                draw_list->AddCircle(pos, NODE_SLOT_RADIUS, color);

                if (curve.locked) continue;

                // io
                ImGui::SetCursorScreenPos(pos - RADIUS);
                ImGui::PushID(id_prefix | j);
                ImGui::InvisibleButton("", RADIUS * 2);
                if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                    m_line = k; m_pKeyframe = pKeyframe; m_handle = j;
                }
                if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f)) {
                    if (j == 0){
                        pKeyframe->set_left_handle_position({ pKeyframe->left_handle.x + mouse_delta.x,  pKeyframe->left_handle.y + mouse_delta.y});
                    } else if (j == 1) {
                        curve.moveKeyframe(pKeyframe, {mouse_delta.x, mouse_delta.y});
                    } else {
                        pKeyframe->set_right_handle_position({ pKeyframe->right_handle.x + mouse_delta.x,  pKeyframe->right_handle.y + mouse_delta.y});
                    }
                }
                ImGui::PopID();
            }
        }
    }

    // canvas io
    ImGui::SetCursorScreenPos(canvas_p0);
    ImGui::InvisibleButton("_canvas_", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);

    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Right, 0.0f)) {
        m_scrolling.x += mouse_delta.x;
        m_scrolling.y += mouse_delta.y * 50;
    }

    if (ImGui::IsItemHovered()) {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            m_line = -1;
            m_handle = -1;
            m_pKeyframe = nullptr;
        }
        auto new_zoom = m_zoom + io.MouseWheel * 0.1f;
        if (new_zoom > ZOOM_MIN && new_zoom < ZOOM_MAX) m_zoom = new_zoom;
    }
}

void ImGui::CustomWidget::CurveEditor::render_right() {
    float f;
    ImGui::DragFloat("Frame", &m_frame);
    ImGui::Text("Active Keyframe");
    if (m_line < 0 || m_line >= CURVE_COUNT) return;
    if (m_pKeyframe == nullptr) return;
    f = m_pKeyframe->keyframe.x; if (ImGui::DragFloat("Key Frame", &f)) m_curves[m_line].moveKeyframe(m_pKeyframe, {f - m_pKeyframe->keyframe.x, 0});
    f = m_pKeyframe->keyframe.y; if (ImGui::DragFloat("Value", &f, 0.01f)) m_pKeyframe->setValue(f);
    f = m_pKeyframe->left_handle.x; if (ImGui::DragFloat("Frame(l)", &f)) m_pKeyframe->set_left_handle_position({f, m_pKeyframe->left_handle.y});
    f = m_pKeyframe->left_handle.y; if (ImGui::DragFloat("Value(l)", &f, 0.01f)) m_pKeyframe->set_left_handle_position({m_pKeyframe->left_handle.x, f});
    f = m_pKeyframe->right_handle.x; if (ImGui::DragFloat("Frame(r)", &f)) m_pKeyframe->set_right_handle_position({f, m_pKeyframe->right_handle.y});
    f = m_pKeyframe->right_handle.y; if (ImGui::DragFloat("Value(r)", &f, 0.01f)) m_pKeyframe->set_right_handle_position({m_pKeyframe->right_handle.x, f});
}

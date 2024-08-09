#pragma once

struct c_splitscreen_config {
    char buffer[240];
    struct config_table_definition {
        struct view_bounds_definition {
            float start_x;
            float start_y;
            float end_x;
            float end_y;
            int type;

            inline bool valid() {
                bool result = true;
                result &= start_x >= 0.0f && start_x <= 1.0f && start_y >= 0.0f && start_y <= 1.0f;
                result &= end_x >= 0.0f && end_x <= 1.0f && end_y >= 0.0f && end_y <= 1.0f;
                result &= start_x != end_x && start_y != end_y;
                return result;
            }

        } m_view_bounds[4];
    } m_config_table[4];

    inline config_table_definition::view_bounds_definition* get_view_bounds(int player_count, int player_index) {
        return &m_config_table[player_count].m_view_bounds[player_index];
    }
};
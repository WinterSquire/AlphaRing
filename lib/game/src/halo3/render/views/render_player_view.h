#pragma once

struct c_player_view {
    struct function_table_definition {
        int (*render)(c_player_view* player_view);
        void* (*render_setup)(c_player_view* player_view);
        void* (*compute_visibility)(c_player_view* player_view);
        void* (*render_submit_visibility)();
    };

    function_table_definition* function_table;
    char buffer[10264];
};

static_assert(sizeof(c_player_view) == 10272);
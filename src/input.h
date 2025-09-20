#pragma once

#include <libmcc/libmcc.h>

enum e_control_mapping_group {
	_control_mapping_group_movement,
	_control_mapping_group_actions,
	_control_mapping_group_vehicle_controls,
	_control_mapping_group_ui_controls,
	_control_mapping_group_forge,
	_control_mapping_group_theater,
	k_control_mapping_group_count
};

constexpr int k_number_of_actions = libmcc::k_game_abstract_button_count;

typedef char t_gamepad_mapping[k_number_of_actions];
typedef char t_keyboard_mouse_mapping[2][k_number_of_actions];

struct s_control_mapping_global {
	char group_action_indices[k_control_mapping_group_count];
	unsigned char actions[k_number_of_actions];
};

extern const libmcc::s_gamepad_mapping g_gamepad_mapping_default;
extern const s_control_mapping_global g_control_mapping_global;

void
import_control_mapping(
	libmcc::s_gamepad_mapping* in,
	t_gamepad_mapping out
);

void
export_control_mapping(
	t_gamepad_mapping in,
	libmcc::s_gamepad_mapping* out
);

void
import_control_mapping(
	libmcc::s_custom_keyboard_mouse_mapping_v2* in,
	t_keyboard_mouse_mapping out
);

void
export_control_mapping(
	t_keyboard_mouse_mapping in,
	libmcc::s_custom_keyboard_mouse_mapping_v2* out
);

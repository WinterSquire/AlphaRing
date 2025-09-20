#pragma once

#include <libmcc/libmcc.h>

enum e_customizable_armor {
	_customizable_armor_helmet,
	_customizable_armor_left_shoulder,
	_customizable_armor_right_shoulder,
	_customizable_armor_chest,
	_customizable_armor_wrist,
	_customizable_armor_utility,
	_customizable_armor_arms,
	_customizable_armor_legs,
	_customizable_armor_backpack,
	_customizable_armor_spartan_body,
	_customizable_armor_spartan_armor_effect,
	_customizable_armor_knees,
	_customizable_armor_visor_color,
	_customizable_armor_elite_helmet,
	_customizable_armor_elite_left_shoulder,
	_customizable_armor_elite_right_shoulder,
	_customizable_armor_elite_chest,
	_customizable_armor_elite_arms,
	_customizable_armor_elite_legs,
	_customizable_armor_elite_armor,
	_customizable_armor_elite_armor_effect,
	_customizable_armor_voice,
	_customizable_armor_player_model_primary_color,
	_customizable_armor_player_model_secondary_color,
	_customizable_armor_player_model_tertiary_color,
	_customizable_armor_spartan_pose,
	_customizable_armor_elite_pose,
	k_customizable_armor_count
};

enum e_customizable_type {
	_customizable_type_armor,
	_customizable_type_weapon,
	_customizable_type_vehicle,
	k_customizable_type_count
};

constexpr int k_maximum_number_of_customization_item = k_customizable_armor_count + 32;
constexpr int k_maximum_number_of_customization_skin = 2176;

/*
	layout: armor + weapon + vehicle
*/
typedef int t_skin_list[k_maximum_number_of_customization_item];
typedef int t_skin_range_list[k_maximum_number_of_customization_item][2]; // [begin, end)

struct s_game_customization_global {
	unsigned char sizes[k_customizable_type_count];
	unsigned char items[k_maximum_number_of_customization_item];
	t_skin_range_list skins;
};

struct s_customization_global {
	s_game_customization_global game_customization_globals[libmcc::k_game_count];
	int skin_count;
	int skins[k_maximum_number_of_customization_skin];
};

extern const s_customization_global g_customization_global;

void
import_skin_list(
	s_game_customization_global* global,
	libmcc::s_player_customization* in,
	t_skin_list out
);

void
export_skin_list(
	s_game_customization_global* global,
	t_skin_list in,
	libmcc::s_player_customization* out
);
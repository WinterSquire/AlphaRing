#include "input.h"

using namespace libmcc;

void
import_control_mapping(
	libmcc::s_gamepad_mapping* in,
	t_gamepad_mapping out
) {
	for (int i = 0; i < k_number_of_actions; ++i) {
		char button = in->actions[i];

		if (button < 0 || button > _abstract_gamepad_button_y) {
			button = -1;
		}

		out[i] = button;
	}
}

void
export_control_mapping(
	t_gamepad_mapping in,
	libmcc::s_gamepad_mapping* out
) {
	for (int i = 0; i < k_number_of_actions; ++i) {
		char button = in[i];

		if (button < 0 || button > _abstract_gamepad_button_y) {
			button = -1;
		}

		out->actions[i] = static_cast<e_abstract_gamepad_button>(button);
	}
}

void
import_control_mapping(
	libmcc::s_custom_keyboard_mouse_mapping_v2* in,
	t_keyboard_mouse_mapping out
) {

}

void
export_control_mapping(
	t_keyboard_mouse_mapping in,
	libmcc::s_custom_keyboard_mouse_mapping_v2* out
) {

}

// control mapping global
struct s_ct_control_mapping_group {
	e_control_mapping_group group;
	std::initializer_list<e_game_abstract_button> actions;
};

struct s_ct_gamepad_action_button {
	e_game_abstract_button action;
	e_abstract_gamepad_button button;
};

struct s_ct_keyboard_mouse_action_key {
	e_game_abstract_button action;
	int primary;
	int secondary;
};

static constexpr s_control_mapping_global
make_control_mapping_global(
	std::initializer_list<s_ct_control_mapping_group> group_list
) {
	auto index = 0;
	s_control_mapping_global result{};
	const s_ct_control_mapping_group* groups[k_control_mapping_group_count]{};

	for (auto& group : group_list) {
		groups[group.group] = &group;
	}

	for (int i = 0; i < k_control_mapping_group_count; ++i) {
		auto group = groups[i];

		if (!group) {
			result.group_action_indices[i] = -1;
			continue;
		}

		for (auto& action : group->actions) {
			result.actions[index] = action;
			++index;
		}

		result.group_action_indices[i] = index;
	}

	return result;
}

static constexpr s_gamepad_mapping
make_gamepad_mapping(
	const std::initializer_list<s_ct_gamepad_action_button>& action_button_list
) {
	s_gamepad_mapping result;

	for (int i = 0; i < k_game_abstract_button_count; ++i) {
		result.actions[i] = k_abstract_gamepad_button_none;
	}

	for (auto& action_button : action_button_list) {
		result.actions[action_button.action] = action_button.button;
	}

	return result;
}

static constexpr s_custom_keyboard_mouse_mapping_v2
make_keyboard_mouse_mapping(
	const std::initializer_list<s_ct_keyboard_mouse_action_key>& mapping
) {
	return s_custom_keyboard_mouse_mapping_v2{};
}

constexpr s_control_mapping_global g_control_mapping_global = make_control_mapping_global(
{ {
	.group = _control_mapping_group_movement,
	.actions = {
		_game_abstract_button_jump,
		_game_abstract_button_crouch,

		_game_abstract_button_sprint,
	}
},{
	.group = _control_mapping_group_actions,
	.actions = {
		_game_abstract_button_fire,
		_game_abstract_button_dualwield,
		_game_abstract_button_zoom,
		_game_abstract_button_meleeattack,
		_game_abstract_button_reload,
		_game_abstract_button_reloadsecondary,
		_game_abstract_button_throwgrenade,
		_game_abstract_button_actionreload,
		_game_abstract_button_switchweapon,
		_game_abstract_button_switchgrenade,
		_game_abstract_button_nextgrenade,
		_game_abstract_button_previousgrenade,
		_game_abstract_button_equipment,
		_game_abstract_button_flashlight,
		_game_abstract_button_swapweapon,

		_game_abstract_button_flashlightalt,
		_game_abstract_button_zoomin,
		_game_abstract_button_zoomout,
		_game_abstract_button_moveforward,
		_game_abstract_button_movebackward,
		_game_abstract_button_strafeleft,
		_game_abstract_button_straferight,
		_game_abstract_button_specialaction,
		_game_abstract_button_loadoutmenu,
		_game_abstract_button_activatewaypoint,
		_game_abstract_button_activatewaypointalt,
		_game_abstract_button_pingnavpoints,
	}
},{
	.group = _control_mapping_group_vehicle_controls,
	.actions = {
		_game_abstract_button_secondaryfire,
		_game_abstract_button_primaryvehicletrick,
		_game_abstract_button_secondaryvehicletrick,
		_game_abstract_button_bansheebomb,
		_game_abstract_button_raisehornet,
		_game_abstract_button_lowerhornet,
	}
},{
	.group = _control_mapping_group_ui_controls,
	.actions = {
		_game_abstract_button_showscores,
	}
},{
	.group = _control_mapping_group_forge,
	.actions = {
		_game_abstract_button_lifteditor,
		_game_abstract_button_dropeditor,
		_game_abstract_button_grabobjecteditor,
		_game_abstract_button_boosteditor,
		_game_abstract_button_croucheditor,
		_game_abstract_button_deleteobjecteditor,
		_game_abstract_button_createobjecteditor,
		_game_abstract_button_opentoolmenueditor,
		_game_abstract_button_switchplayermodeeditor,
		_game_abstract_button_scopezoomeditor,
		_game_abstract_button_playerlockformanipulationeditor,
		_game_abstract_button_togglerotationaxeseditor,

		_game_abstract_button_duplicateobjecteditor,
		_game_abstract_button_lockobjecteditor,
		_game_abstract_button_resetorientationeditor,
	}
}, {
	.group = _control_mapping_group_theater,
	.actions = {
		_game_abstract_button_showhidepanneltheater,
		_game_abstract_button_showhideinterfacetheater,
		_game_abstract_button_togglefirstthirdpersonviewtheater,
		_game_abstract_button_camerafocustheater,
		_game_abstract_button_fastforwardtheater,
		_game_abstract_button_fastrewindtheater,
		_game_abstract_button_stopcontinueplaybacktheater,
		_game_abstract_button_playbackspeeduptheater,
		_game_abstract_button_enterfreecameramodetheater,
		_game_abstract_button_movementspeeduptheater,
		_game_abstract_button_panningcameratheater,
		_game_abstract_button_cameramoveuptheater,
		_game_abstract_button_cameramovedowntheater,
		_game_abstract_button_zoomcameratheater,
	}
} });

constexpr s_gamepad_mapping g_gamepad_mapping_default = make_gamepad_mapping({
	// movement
	{_game_abstract_button_jump,                                _abstract_gamepad_button_a},
	{_game_abstract_button_crouch,                              _abstract_gamepad_button_left_stick},

	{_game_abstract_button_sprint,                              _abstract_gamepad_button_left_bumper},

	// actions
	{_game_abstract_button_fire,                                _abstract_gamepad_button_right_trigger},
	{_game_abstract_button_dualwield,                           _abstract_gamepad_button_left_trigger},
	{_game_abstract_button_zoom,                                _abstract_gamepad_button_right_stick},
	{_game_abstract_button_meleeattack,                         _abstract_gamepad_button_b},
	{_game_abstract_button_reload,                              _abstract_gamepad_button_right_bumper},
	{_game_abstract_button_reloadsecondary,                     _abstract_gamepad_button_left_bumper},
	{_game_abstract_button_throwgrenade,                        _abstract_gamepad_button_left_trigger},
	{_game_abstract_button_actionreload,                        _abstract_gamepad_button_right_bumper},
	{_game_abstract_button_switchweapon,                        _abstract_gamepad_button_y},
	{_game_abstract_button_switchgrenade,                       _abstract_gamepad_button_left_bumper},
	{_game_abstract_button_nextgrenade,                         _abstract_gamepad_button_right},
	{_game_abstract_button_previousgrenade,                     _abstract_gamepad_button_left},
	{_game_abstract_button_equipment,                           _abstract_gamepad_button_x},
	{_game_abstract_button_flashlight,                          _abstract_gamepad_button_up},
	{_game_abstract_button_swapweapon,                          _abstract_gamepad_button_left_bumper},

	{_game_abstract_button_flashlightalt,                       _abstract_gamepad_button_left_bumper},
	{_game_abstract_button_zoomin,                              _abstract_gamepad_button_up},
	{_game_abstract_button_zoomout,                             _abstract_gamepad_button_down},
	{_game_abstract_button_moveforward,                         _abstract_gamepad_button_up},
	{_game_abstract_button_movebackward,                        _abstract_gamepad_button_down},
	{_game_abstract_button_strafeleft,                          _abstract_gamepad_button_left},
	{_game_abstract_button_straferight,                         _abstract_gamepad_button_right},
	{_game_abstract_button_specialaction,                       _abstract_gamepad_button_up},
	{_game_abstract_button_loadoutmenu,                         _abstract_gamepad_button_y},
	{_game_abstract_button_activatewaypoint,                    _abstract_gamepad_button_up},
	{_game_abstract_button_activatewaypointalt,                 _abstract_gamepad_button_down},
	{_game_abstract_button_pingnavpoints,                       _abstract_gamepad_button_down},

	// vehicle controls
	{_game_abstract_button_secondaryfire,                       _abstract_gamepad_button_left_trigger},
	{_game_abstract_button_primaryvehicletrick,                 _abstract_gamepad_button_a},
	{_game_abstract_button_secondaryvehicletrick,               _abstract_gamepad_button_a},
	{_game_abstract_button_bansheebomb,                         _abstract_gamepad_button_b},
	{_game_abstract_button_raisehornet,                         _abstract_gamepad_button_a},
	{_game_abstract_button_lowerhornet,                         _abstract_gamepad_button_left_bumper},

	// ui contorls
	{_game_abstract_button_showscores,                          _abstract_gamepad_button_start},

	// forge
	{_game_abstract_button_lifteditor,                          _abstract_gamepad_button_right_bumper},
	{_game_abstract_button_dropeditor,                          _abstract_gamepad_button_left_bumper},
	{_game_abstract_button_grabobjecteditor,                    _abstract_gamepad_button_a},
	{_game_abstract_button_boosteditor,                         _abstract_gamepad_button_left_trigger},
	{_game_abstract_button_croucheditor,                        _abstract_gamepad_button_left_stick},
	{_game_abstract_button_deleteobjecteditor,                  _abstract_gamepad_button_y},
	{_game_abstract_button_createobjecteditor,                  _abstract_gamepad_button_x},
	{_game_abstract_button_opentoolmenueditor,                  _abstract_gamepad_button_b},
	{_game_abstract_button_switchplayermodeeditor,              _abstract_gamepad_button_up},
	{_game_abstract_button_scopezoomeditor,                     _abstract_gamepad_button_right_stick},
	{_game_abstract_button_playerlockformanipulationeditor,     _abstract_gamepad_button_right_trigger},
	{_game_abstract_button_togglerotationaxeseditor,            _abstract_gamepad_button_down},

	{_game_abstract_button_duplicateobjecteditor,               _abstract_gamepad_button_down},
	{_game_abstract_button_lockobjecteditor,                    _abstract_gamepad_button_left},
	{_game_abstract_button_resetorientationeditor,              _abstract_gamepad_button_right},

	// theater
	{_game_abstract_button_showhidepanneltheater,               _abstract_gamepad_button_x},
	{_game_abstract_button_showhideinterfacetheater,            _abstract_gamepad_button_b},
	{_game_abstract_button_togglefirstthirdpersonviewtheater,   _abstract_gamepad_button_right_stick},
	{_game_abstract_button_camerafocustheater,                  _abstract_gamepad_button_left_stick},
	{_game_abstract_button_fastforwardtheater,                  _abstract_gamepad_button_right},
	{_game_abstract_button_fastrewindtheater,                   _abstract_gamepad_button_left},
	{_game_abstract_button_stopcontinueplaybacktheater,         _abstract_gamepad_button_a},
	{_game_abstract_button_playbackspeeduptheater,              _abstract_gamepad_button_right_trigger},
	{_game_abstract_button_enterfreecameramodetheater,          _abstract_gamepad_button_y},
	{_game_abstract_button_movementspeeduptheater,              _abstract_gamepad_button_left_trigger},
	{_game_abstract_button_panningcameratheater,                _abstract_gamepad_button_left_stick},
	{_game_abstract_button_cameramoveuptheater,                 _abstract_gamepad_button_right_bumper},
	{_game_abstract_button_cameramovedowntheater,               _abstract_gamepad_button_left_bumper},
	{_game_abstract_button_zoomcameratheater,                   _abstract_gamepad_button_right_stick},
});
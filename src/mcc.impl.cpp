#include "mcc.h"
#include "player.h"

#include <Xinput.h>

using namespace libmcc;

// forward declare
void game_globals_state_launch_update(s_game_globals* game_globals);
void game_globals_state_exit_enter(s_game_globals* game_globals);
void game_globals_state_start_update(s_game_globals* game_globals);
s_player_profile* local_user_get_profile(i_game_manager* This, XUID xuid);
bool input_update(i_game_manager* This, e_local_player player, s_input_state* state);
void input_set_rumble(i_game_manager* This, e_local_player player, s_rumble_state* state);
bool local_user_get_player(i_game_manager* This, XUID* xuid, wchar_t* name, uint32_t size, e_local_player player);
s_gamepad_mapping* local_user_get_gamepad_mapping(i_game_manager* This, XUID xuid);

libmcc::s_game_globals_states g_o_game_state_ftable;
libmcc::i_game_manager_vftable g_o_game_manager_vftable;

s_game_globals_states g_m_game_state_ftable{
	.enter = {
		nullptr,
		nullptr,
		game_globals_state_start_update,
		game_globals_state_exit_enter,
	},
	.update = {
		nullptr,
		game_globals_state_launch_update,
		nullptr,
		nullptr,
	},
};

i_game_manager_vftable g_m_game_manager_vftable{
	.local_user_get_profile = local_user_get_profile,
	.input_update = input_update,
	.input_set_rumble = input_set_rumble,
	.local_user_get_player = local_user_get_player,
	.local_user_get_gamepad_mapping = local_user_get_gamepad_mapping
};

/*
	On count down finished, before create game engine
	In this phase, we will apply the patch enabled
*/
static void
game_globals_state_launch_update(
	s_game_globals* game_globals
) {
	if (g_o_game_state_ftable.update[_game_globals_state_launch])
		g_o_game_state_ftable.update[_game_globals_state_launch](game_globals);
}

/*
	On game exit
	In this phase, we will destory the patch
*/
static void
game_globals_state_exit_enter(
	s_game_globals* game_globals
) {
	if (g_o_game_state_ftable.enter[_game_globals_state_exit])
		g_o_game_state_ftable.update[_game_globals_state_exit](game_globals);
}

/*
	On game finished loading
*/
static void
game_globals_state_start_update(
	s_game_globals* game_globals
) {
	if (g_o_game_state_ftable.update[_game_globals_state_start])
		g_o_game_state_ftable.update[_game_globals_state_start](game_globals);
}

/*
	Get local player profile
*/
static s_player_profile*
local_user_get_profile(
	i_game_manager* This, 
	XUID xuid
) {
	auto player = get_local_player_index(xuid);
	if (player >= 0) return &g_local_player_global.profiles[player].profile;
	else return g_o_game_manager_vftable.local_user_get_profile(This, xuid);
}

/*
	Get local player gamepad mapping
*/
static s_gamepad_mapping*
local_user_get_gamepad_mapping(
	i_game_manager* This,
	XUID xuid
) {
	auto player = get_local_player_index(xuid);
	if (player >= 0) return &g_local_player_global.profiles[player].mapping;
	else return g_o_game_manager_vftable.local_user_get_gamepad_mapping(This, xuid);
}

/*
	Get player input state
	Always return true, otherwise the game may freeze.
*/
static bool
input_update(
	i_game_manager* This, 
	e_local_player player, 
	s_input_state* state
) {
	XINPUT_STATE xstate;
	auto input_device = get_local_player_input_device_index(player);

	switch (input_device) {
	// None
	case -2: 
		break;

	// K/M
	case -1: 
		state->is_km = true; 
		g_o_game_manager_vftable.input_update(This, player, state);
		break;

	// Gamepad
	default: 
		ZeroMemory(&xstate, sizeof(xstate));
		XInputGetState(input_device, &xstate);
		state->gamepad.buttons = xstate.Gamepad.wButtons;
		state->gamepad.leftTrigger = xstate.Gamepad.bLeftTrigger;
		state->gamepad.rightTrigger = xstate.Gamepad.bRightTrigger;
		state->gamepad.thumbLX = xstate.Gamepad.sThumbLX;
		state->gamepad.thumbLY = xstate.Gamepad.sThumbLY;
		state->gamepad.thumbRX = xstate.Gamepad.sThumbRX;
		state->gamepad.thumbRY = xstate.Gamepad.sThumbRY;
		break;
	}

	return true;
}

/*
	Set local player gamepad rumble state
*/
static void
input_set_rumble(
	i_game_manager* This, 
	e_local_player player, 
	s_rumble_state* state
) {
	XINPUT_VIBRATION xstate;
	auto input_device = get_local_player_input_device_index(player);

	if (input_device < 0) return;

	xstate.wLeftMotorSpeed = state->left_motor_speed;
	xstate.wRightMotorSpeed = state->right_motor_speed;

	XInputSetState(input_device, &xstate);
}

/*
	Get local player
*/
static bool
local_user_get_player(
	i_game_manager* This, 
	XUID* id, 
	wchar_t* name, 
	uint32_t size, 
	e_local_player player
) {
	s_local_player_global* global = nullptr;

	if (player < 0 || player >= global->number_of_local_player)
		return false;

	if (id) *id = global->ids[player];
	if (name) memcpy(name, global->names[player], min(size, 0x20));
	
	return true;
}
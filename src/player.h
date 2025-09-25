#pragma once

#include <libmcc/libmcc.h>

/*
halo3:
foreach player
	get_player_xuid

foreach player
	get_player_xuid
	get_player_profile
	get_User_Preferred_Input_Device
	if use_mapping
		get_player_profile
		get_player_gamepad_mapping
*/

enum e_input_device {
	_input_device_none,
	_input_device_controller1,
	_input_device_controller2,
	_input_device_controller3,
	_input_device_controller4,
	_input_device_keyboard_and_mouse,
};

struct s_local_player_global {
	bool override_profile;
	int number_of_local_player;
	char input_devices[4];
	unsigned long long ids[4];
	wchar_t names[4][0x20];
	struct {
		libmcc::s_player_profile profile;
		libmcc::s_gamepad_mapping mapping;
	} profiles[4];
};

extern s_local_player_global g_local_player_global;

int player_initialize();

/*
	Get local player input device index
	0	: None
	1-4 : Gamepad
	5	: k/M
*/
int get_local_player_input_device_index(int local_player);

/*
	Get local player index
	-1 : None
	0-3: Player
*/
int get_local_player_index(unsigned long long id);
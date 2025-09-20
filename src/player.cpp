#include "player.h"

s_local_player_global g_local_player_global;

int get_local_player_input_device_index(int local_player) {
	if (local_player < 0 || local_player >= g_local_player_global.number_of_local_player)
		return -2;
	else
		return g_local_player_global.input_devices[local_player];
}

int get_local_player_index(unsigned long long id) {
	int player = -1;

	for (int i = 0; i < 4; ++i) {
		if (id != g_local_player_global.ids[i])
			continue;
		player = i;
	}

	if (!player && !g_local_player_global.override_profile) {
		player = -1;
	}

	return player;
}
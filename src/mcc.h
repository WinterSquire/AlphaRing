#pragma once

#include <libmcc/libmcc.h>

#include "common.h"

enum e_mcc_offset {
	_mcc_offset_MCCGameInstance_vInit,
	_mcc_offset_MCCGameState_vftable,
	_mcc_offset_MCCGameManager_vftable,

	k_mcc_offset_count
};

constexpr size_t k_mcc_steam_offset_table[k_mcc_offset_count]{
	0x2965AC8,
	0x3F66890,
	0x327F3C0,
};

constexpr size_t k_mcc_winstore_offset_table[k_mcc_offset_count]{
	// todo
};

struct s_mcc_global {
	int type;
	int game_type;
	void* instance;
	void* game_instnce;
};

extern s_mcc_global g_mcc_global;
extern libmcc::s_game_globals_states g_m_game_state_ftable;
extern libmcc::s_game_globals_states g_o_game_state_ftable;
extern libmcc::i_game_manager_vftable g_m_game_manager_vftable;
extern libmcc::i_game_manager_vftable g_o_game_manager_vftable;

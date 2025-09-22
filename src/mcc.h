#pragma once

#include "common.h"

enum e_mcc_type {
	_mcc_type_steam,
	_mcc_type_winstore
};

enum e_mcc_offset {
	_mcc_offset_MCCGameInstance_vInit,
	_mcc_offset_MCCGameState_vftable,
	_mcc_offset_MCCGameManager_vftable,

	k_mcc_offset_count
};

typedef std::array<size_t, k_mcc_offset_count> t_mcc_offset_table;
typedef std::array<void*, k_mcc_offset_count> t_mcc_address_table;

const t_mcc_offset_table*
get_offset_table(e_mcc_type type, s_version version);

extern libmcc::s_game_globals_states g_m_game_state_ftable;
extern libmcc::s_game_globals_states g_o_game_state_ftable;
extern libmcc::i_game_manager_vftable g_m_game_manager_vftable;
extern libmcc::i_game_manager_vftable g_o_game_manager_vftable;

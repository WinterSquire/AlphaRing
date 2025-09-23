#include "mcc.h"

struct s_mcc_offset_table_record{
	bool valid;
	e_mcc_type type;
	s_version version;
	t_mcc_offset_table table;
};

typedef std::array<s_mcc_offset_table_record, 4> t_mcc_offset_table_record_list;

extern const t_mcc_offset_table_record_list g_mcc_offset_table_record_list;

const t_mcc_offset_table*
get_offset_table(e_mcc_type type, s_version version) {
	for (auto& record : g_mcc_offset_table_record_list) {
		if (!record.valid || record.type != type || record.version.ull != version.ull)
			continue;
		return &record.table;
	}
	return NULL;
}

constexpr t_mcc_offset_table_record_list g_mcc_offset_table_record_list{
	s_mcc_offset_table_record{
		false,
		_mcc_type_steam,
		{ 1,3528,0,0 },
		{
			0x2965AC8,
			0x3F66890,
			0x327F3C0,
		}
	},
	s_mcc_offset_table_record{
		false,
		_mcc_type_winstore,
		{ 1,3528,0,0 },
		{
			0x2835448,
			0x3DB4F10,
			0x3122380,
		}
	},
	s_mcc_offset_table_record{
		false,
		_mcc_type_steam, 
		{ 1,3495,0,0 },
		{
			0x2965AC8,
			0x3F66890,
			0x327F3C0,
		}
	},
	s_mcc_offset_table_record{
		false,
		_mcc_type_winstore,
		{ 1,3495,0,0 },
		{
			0x2835448,
			0x3DB4F10,
			0x3122380,
		}
	},
};
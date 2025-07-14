#include "mcc_manager.h"

#include "./mcc_impl.h"
#include "./player_manager.h"
#include "../d3d11/d3d11_manager.h"
#include "module_manager.h"

using namespace libmcc;

static bool d3ddebug() {
	return true;
}

int c_mcc_manager::initialize() {
	if (m_initialized) {
		return 0;
	}

	// Initialize variables
	m_game_module = k_module_none;

	// Initialize hook
	hook_manager()->initialize();

	module_manager()->initialize();

	event_queue_manager()->initialize();

	// Initialize env
	allocate_console();

	initialize_base_dir();

	// Initialize Game
	// Get Executable Name
	auto name = get_module_name(m_hModule);

	if (name == MCC_MODULE_NAME) {
		m_mcc_module = _module_mcc;
	} else if (name == MCCWINSTORE_MODULE_NAME) {
		m_mcc_module = _module_mccwinstore;
	} else {
		m_mcc_module = k_module_none;
		ASSERTF(false, "Executable is not valid: {}, please use this mod with MCC only!", name);
	}
	
	// Get Game Version
	m_version = get_file_version(m_hModule);

	LOG_INFO("{}:[{}]", (int)m_mcc_module, m_version.to_string());

	// override game manager vftable
	auto vftable = *get_runtime_address(g_mcc_offset_map.game_manager_vftable);

	vftable_manager()->create(
		vftable, 
		(const void**)&g_game_manager_vftable, 
		sizeof(i_game_manager_vftable), 
		(void**)&g_game_manager_vftable_original);

	vftable_manager()->enable(vftable);

	auto func = get_runtime_address(g_mcc_offset_map.set_player_input);

	hook_manager()->create(
		func,
		(void*)&set_player_gamepad,
		(void**)&set_player_gamepad_original
	);

	hook_manager()->enable(func);

	// Initialize the player manager
	player_manager()->initialize();

	// Initialize the d3d11
	Sleep(1500);
	d3d11_manager()->initialize();

	// Wait for MCC to initialize
	while(true) {
		auto game_globals = *libmcc::mcc::g_game_globals();

		if (game_globals == nullptr) {
			Sleep(1000);
			continue;
		}

		auto game_globals_states = get_runtime_address(g_mcc_offset_map.game_globals_states);

		auto result = vftable_manager()->create(
			game_globals_states,
			(const void**)&g_game_globals_states,
			sizeof(s_game_globals_states),
			(void**)&g_game_globals_states_original);

		vftable_manager()->enable(result);

		break;
	}

	m_initialized = true;

	return 0;
}

int c_mcc_manager::shutdown() {
	if (!m_initialized) {
		return 0;
	}

	player_manager()->shutdown();

	d3d11_manager()->shutdown();

	module_manager()->shutdown();

	hook_manager()->shutdown();

	event_queue_manager()->shutdown();

	free_console();

	m_initialized = false;

	return 0;
}

HANDLE c_mcc_manager::attach(HMODULE hModule) {
	m_hModule = hModule;

	auto func = [](LPVOID lpThreadParameter) -> DWORD {
		return reinterpret_cast<c_mcc_manager*>(lpThreadParameter)->initialize();
	};

	return CreateThread(nullptr, 0, func, this, 0, nullptr);
}

void c_mcc_manager::detach() {
	shutdown();
}

int c_mcc_manager::initialize_base_dir() {
	auto module_path = get_document_folder_path();

	auto base_dir = std::filesystem::path(module_path).append(BASE_DIR);

	m_cwd = std::filesystem::absolute(base_dir);
	
	return check_directory(m_cwd.c_str(), true);
}

std::unique_ptr<std::vector<char>> c_mcc_manager::read_resource(const char* resource) {
	return read_file(std::filesystem::path(m_cwd).append(resource).c_str());
}

bool c_mcc_manager::write_resource(const char* resource, const char* data, size_t size) {
	return write_file(std::filesystem::path(m_cwd).append(resource).c_str(), data, size);
}

int c_mcc_manager::allocate_console() {
	bool result = AllocConsole();

	ASSERT(result, "Failed to allocate console!");

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	return result;
}

int c_mcc_manager::free_console() {
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);

	return FreeConsole();
}

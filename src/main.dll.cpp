#include "mcc.h"
#include "win32helper.h"

using namespace libmcc;

typedef void (*t_UMCCGameInstanceInit)(void* instance);

struct s_mcc_global {
	int mcc_type;
	int halo_type;
	s_version version;
	void* mcc_instance;
	void* halo_instnce;
	t_mcc_address_table address_table;
	t_UMCCGameInstanceInit UMCCGameInstanceInit;
};

static s_mcc_global g_mcc_global;

/*
	[Window Thread] Wrapper for the main window thread
*/
static DWORD
main_thread(LPVOID lpThreadParameter) {
	extern int APIENTRY
	WinMain(
		HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nShowCmd
	);

	return WinMain(NULL, NULL, NULL, NULL);
}

/*
	[Game Thread] Initialization
*/
static void
UMCCGameInstanceInit(void* instance) {
	auto write_ftable = [](
		void* dst, 
		void** src, 
		void** ori, 
		void** tmp, 
		size_t size
	) -> void {
		auto lob = sizeof(void*) * size;

		memcpy(ori, dst, lob);
		memcpy(tmp, dst, lob);

		for (int i = 0; i < size; ++i) {
			if (src[i] != NULL) tmp[i] = src[i];
		}

		win32_write_memory(dst, tmp, lob);
	};

	libmcc::s_game_globals_states game_state_ftable_tmp;
	libmcc::i_game_manager_vftable game_manager_vftable_tmp;

	// invoke original function
	g_mcc_global.UMCCGameInstanceInit(instance);

	// patch function tables
	write_ftable(
		g_mcc_global.address_table[_mcc_offset_MCCGameState_vftable],
		(void**)&g_m_game_state_ftable,
		(void**)&g_o_game_state_ftable,
		(void**)&game_state_ftable_tmp,
		sizeof(game_state_ftable_tmp) / sizeof(void*)
	);

	write_ftable(
		g_mcc_global.address_table[_mcc_offset_MCCGameManager_vftable],
		(void**)&g_m_game_manager_vftable,
		(void**)&g_o_game_manager_vftable,
		(void**)&game_manager_vftable_tmp,
		sizeof(game_manager_vftable_tmp) / sizeof(void*)
	);

	// create window thread
	CreateThread(
		NULL,
		NULL,
		main_thread,
		NULL,
		NULL,
		NULL
	);
}

/*
	[Main Thread] DLL Main
*/
BOOL APIENTRY
DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
	auto set_address_table = [](
		void* base,
		const t_mcc_offset_table* in,
		t_mcc_address_table* out
	) -> void {
		for (int i = 0; i < k_mcc_offset_count; ++i) {
			out->at(i) = reinterpret_cast<char*>(base) + in->at(i);
		}
	};

	auto write_pointer = [](
		void* src,
		void** dst,
		void** original
	) -> void {
		auto tmp = src;
		*original = *dst;
		win32_write_memory(dst, &tmp, sizeof(void*));
	};

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		auto type = _mcc_type_steam;
		auto module = GetModuleHandle(NULL);
		auto name = win32_get_export_name(module);
		auto version = win32_get_version(module);		

		// check executable
		if (!strcmp(name, "MCCWinStore-Win64-Shipping.exe")) {
			type = _mcc_type_winstore;
		} else if (strcmp(name, "MCC-Win64-Shipping.exe")) {
			MessageBox(
				NULL, 
				TEXT("This mod won't be initialized."), 
				TEXT("Invalid Game"), 
				MB_OK
			);
			break;
		}

		g_mcc_global.mcc_type = type;
		g_mcc_global.mcc_instance = module;

		// setup address table
		auto table = get_offset_table(type, version);

		if (table == NULL) {
			MessageBox(
				NULL, 
				TEXT("This mod won't be initialized."), 
				TEXT("Unsupported Version"), 
				MB_OK
			);
			break;
		}

		set_address_table(
			module, 
			table, 
			&g_mcc_global.address_table
		);

		write_pointer(
			(void*)UMCCGameInstanceInit,
			(void**)g_mcc_global.address_table[_mcc_offset_MCCGameInstance_vInit],
			(void**)&g_mcc_global.UMCCGameInstanceInit
		);		

		break;
	}
	default:
		break;
	}

	return TRUE;
}

// export function (MSVC)
#pragma comment(linker, "/export:IsInteractiveUserSession=\"C:\\Windows\\System32\\wtsapi32.IsInteractiveUserSession\"")
#pragma comment(linker, "/export:QueryActiveSession=\"C:\\Windows\\System32\\wtsapi32.QueryActiveSession\"")
#pragma comment(linker, "/export:QueryUserToken=\"C:\\Windows\\System32\\wtsapi32.QueryUserToken\"")
#pragma comment(linker, "/export:RegisterUsertokenForNoWinlogon=\"C:\\Windows\\System32\\wtsapi32.RegisterUsertokenForNoWinlogon\"")
#pragma comment(linker, "/export:WTSCloseServer=\"C:\\Windows\\System32\\wtsapi32.WTSCloseServer\"")
#pragma comment(linker, "/export:WTSConnectSessionA=\"C:\\Windows\\System32\\wtsapi32.WTSConnectSessionA\"")
#pragma comment(linker, "/export:WTSConnectSessionW=\"C:\\Windows\\System32\\wtsapi32.WTSConnectSessionW\"")
#pragma comment(linker, "/export:WTSCreateListenerA=\"C:\\Windows\\System32\\wtsapi32.WTSCreateListenerA\"")
#pragma comment(linker, "/export:WTSCreateListenerW=\"C:\\Windows\\System32\\wtsapi32.WTSCreateListenerW\"")
#pragma comment(linker, "/export:WTSDisconnectSession=\"C:\\Windows\\System32\\wtsapi32.WTSDisconnectSession\"")
#pragma comment(linker, "/export:WTSEnableChildSessions=\"C:\\Windows\\System32\\wtsapi32.WTSEnableChildSessions\"")
#pragma comment(linker, "/export:WTSEnumerateListenersA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateListenersA\"")
#pragma comment(linker, "/export:WTSEnumerateListenersW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateListenersW\"")
#pragma comment(linker, "/export:WTSEnumerateProcessesA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateProcessesA\"")
#pragma comment(linker, "/export:WTSEnumerateProcessesExA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateProcessesExA\"")
#pragma comment(linker, "/export:WTSEnumerateProcessesExW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateProcessesExW\"")
#pragma comment(linker, "/export:WTSEnumerateProcessesW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateProcessesW\"")
#pragma comment(linker, "/export:WTSEnumerateServersA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateServersA\"")
#pragma comment(linker, "/export:WTSEnumerateServersW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateServersW\"")
#pragma comment(linker, "/export:WTSEnumerateSessionsA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateSessionsA\"")
#pragma comment(linker, "/export:WTSEnumerateSessionsExA=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateSessionsExA\"")
#pragma comment(linker, "/export:WTSEnumerateSessionsExW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateSessionsExW\"")
#pragma comment(linker, "/export:WTSEnumerateSessionsW=\"C:\\Windows\\System32\\wtsapi32.WTSEnumerateSessionsW\"")
#pragma comment(linker, "/export:WTSFreeMemory=\"C:\\Windows\\System32\\wtsapi32.WTSFreeMemory\"")
#pragma comment(linker, "/export:WTSFreeMemoryExA=\"C:\\Windows\\System32\\wtsapi32.WTSFreeMemoryExA\"")
#pragma comment(linker, "/export:WTSFreeMemoryExW=\"C:\\Windows\\System32\\wtsapi32.WTSFreeMemoryExW\"")
#pragma comment(linker, "/export:WTSGetChildSessionId=\"C:\\Windows\\System32\\wtsapi32.WTSGetChildSessionId\"")
#pragma comment(linker, "/export:WTSGetListenerSecurityA=\"C:\\Windows\\System32\\wtsapi32.WTSGetListenerSecurityA\"")
#pragma comment(linker, "/export:WTSGetListenerSecurityW=\"C:\\Windows\\System32\\wtsapi32.WTSGetListenerSecurityW\"")
#pragma comment(linker, "/export:WTSIsChildSessionsEnabled=\"C:\\Windows\\System32\\wtsapi32.WTSIsChildSessionsEnabled\"")
#pragma comment(linker, "/export:WTSLogoffSession=\"C:\\Windows\\System32\\wtsapi32.WTSLogoffSession\"")
#pragma comment(linker, "/export:WTSOpenServerA=\"C:\\Windows\\System32\\wtsapi32.WTSOpenServerA\"")
#pragma comment(linker, "/export:WTSOpenServerExA=\"C:\\Windows\\System32\\wtsapi32.WTSOpenServerExA\"")
#pragma comment(linker, "/export:WTSOpenServerExW=\"C:\\Windows\\System32\\wtsapi32.WTSOpenServerExW\"")
#pragma comment(linker, "/export:WTSOpenServerW=\"C:\\Windows\\System32\\wtsapi32.WTSOpenServerW\"")
#pragma comment(linker, "/export:WTSQueryListenerConfigA=\"C:\\Windows\\System32\\wtsapi32.WTSQueryListenerConfigA\"")
#pragma comment(linker, "/export:WTSQueryListenerConfigW=\"C:\\Windows\\System32\\wtsapi32.WTSQueryListenerConfigW\"")
#pragma comment(linker, "/export:WTSQuerySessionInformationA=\"C:\\Windows\\System32\\wtsapi32.WTSQuerySessionInformationA\"")
#pragma comment(linker, "/export:WTSQuerySessionInformationW=\"C:\\Windows\\System32\\wtsapi32.WTSQuerySessionInformationW\"")
#pragma comment(linker, "/export:WTSQueryUserConfigA=\"C:\\Windows\\System32\\wtsapi32.WTSQueryUserConfigA\"")
#pragma comment(linker, "/export:WTSQueryUserConfigW=\"C:\\Windows\\System32\\wtsapi32.WTSQueryUserConfigW\"")
#pragma comment(linker, "/export:WTSQueryUserToken=\"C:\\Windows\\System32\\wtsapi32.WTSQueryUserToken\"")
#pragma comment(linker, "/export:WTSRegisterSessionNotification=\"C:\\Windows\\System32\\wtsapi32.WTSRegisterSessionNotification\"")
#pragma comment(linker, "/export:WTSRegisterSessionNotificationEx=\"C:\\Windows\\System32\\wtsapi32.WTSRegisterSessionNotificationEx\"")
#pragma comment(linker, "/export:WTSSendMessageA=\"C:\\Windows\\System32\\wtsapi32.WTSSendMessageA\"")
#pragma comment(linker, "/export:WTSSendMessageW=\"C:\\Windows\\System32\\wtsapi32.WTSSendMessageW\"")
#pragma comment(linker, "/export:WTSSetListenerSecurityA=\"C:\\Windows\\System32\\wtsapi32.WTSSetListenerSecurityA\"")
#pragma comment(linker, "/export:WTSSetListenerSecurityW=\"C:\\Windows\\System32\\wtsapi32.WTSSetListenerSecurityW\"")
#pragma comment(linker, "/export:WTSSetRenderHint=\"C:\\Windows\\System32\\wtsapi32.WTSSetRenderHint\"")
#pragma comment(linker, "/export:WTSSetSessionInformationA=\"C:\\Windows\\System32\\wtsapi32.WTSSetSessionInformationA\"")
#pragma comment(linker, "/export:WTSSetSessionInformationW=\"C:\\Windows\\System32\\wtsapi32.WTSSetSessionInformationW\"")
#pragma comment(linker, "/export:WTSSetUserConfigA=\"C:\\Windows\\System32\\wtsapi32.WTSSetUserConfigA\"")
#pragma comment(linker, "/export:WTSSetUserConfigW=\"C:\\Windows\\System32\\wtsapi32.WTSSetUserConfigW\"")
#pragma comment(linker, "/export:WTSShutdownSystem=\"C:\\Windows\\System32\\wtsapi32.WTSShutdownSystem\"")
#pragma comment(linker, "/export:WTSStartRemoteControlSessionA=\"C:\\Windows\\System32\\wtsapi32.WTSStartRemoteControlSessionA\"")
#pragma comment(linker, "/export:WTSStartRemoteControlSessionW=\"C:\\Windows\\System32\\wtsapi32.WTSStartRemoteControlSessionW\"")
#pragma comment(linker, "/export:WTSStopRemoteControlSession=\"C:\\Windows\\System32\\wtsapi32.WTSStopRemoteControlSession\"")
#pragma comment(linker, "/export:WTSTerminateProcess=\"C:\\Windows\\System32\\wtsapi32.WTSTerminateProcess\"")
#pragma comment(linker, "/export:WTSUnRegisterSessionNotification=\"C:\\Windows\\System32\\wtsapi32.WTSUnRegisterSessionNotification\"")
#pragma comment(linker, "/export:WTSUnRegisterSessionNotificationEx=\"C:\\Windows\\System32\\wtsapi32.WTSUnRegisterSessionNotificationEx\"")
#pragma comment(linker, "/export:WTSVirtualChannelClose=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelClose\"")
#pragma comment(linker, "/export:WTSVirtualChannelOpen=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelOpen\"")
#pragma comment(linker, "/export:WTSVirtualChannelOpenEx=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelOpenEx\"")
#pragma comment(linker, "/export:WTSVirtualChannelPurgeInput=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelPurgeInput\"")
#pragma comment(linker, "/export:WTSVirtualChannelPurgeOutput=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelPurgeOutput\"")
#pragma comment(linker, "/export:WTSVirtualChannelQuery=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelQuery\"")
#pragma comment(linker, "/export:WTSVirtualChannelRead=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelRead\"")
#pragma comment(linker, "/export:WTSVirtualChannelWrite=\"C:\\Windows\\System32\\wtsapi32.WTSVirtualChannelWrite\"")
#pragma comment(linker, "/export:WTSWaitSystemEvent=\"C:\\Windows\\System32\\wtsapi32.WTSWaitSystemEvent\"")

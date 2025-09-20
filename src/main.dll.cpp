#include "win32helper.h"
#include "common.h"
#include "mcc.h"

#include <cassert>

using namespace libmcc;

extern int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

// helper function
static void
write_ftable(void* dst, void** src, void** ori, void** tmp, size_t size) {
	auto lob = sizeof(void*) * size;

	memcpy(ori, dst, lob);
	memcpy(tmp, dst, lob);

	for (int i = 0; i < size; ++i) {
		if (src[i] != NULL) tmp[i] = src[i];
	}

	win32_write_memory(dst, tmp, lob);
}

typedef void (*t_UMCCGameInstanceInit)(void* instance);
static t_UMCCGameInstanceInit g_UMCCGameInstanceInit;
static void* g_mcc_address_table[k_mcc_offset_count];

static void
UMCCGameInstanceInit(void* instance) {
	libmcc::s_game_globals_states game_state_ftable_tmp;
	libmcc::i_game_manager_vftable game_manager_vftable_tmp;

	g_UMCCGameInstanceInit(instance);

	write_ftable(
		g_mcc_address_table[_mcc_offset_MCCGameState_vftable],
		(void**)&g_m_game_state_ftable,
		(void**)&g_o_game_state_ftable,
		(void**)&game_state_ftable_tmp,
		sizeof(game_state_ftable_tmp) / sizeof(void*)
	);

	write_ftable(
		g_mcc_address_table[_mcc_offset_MCCGameManager_vftable],
		(void**)&g_m_game_manager_vftable,
		(void**)&g_o_game_manager_vftable,
		(void**)&game_manager_vftable_tmp,
		sizeof(game_manager_vftable_tmp) / sizeof(void*)
	);
}

BOOL APIENTRY
DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		auto type = 0;
		auto module = GetModuleHandle(NULL);
		auto name = win32_get_export_name(module);
		auto version = win32_get_version(module);
		auto offset_table = k_mcc_steam_offset_table;

		// check executable and version
		if (!strcmp(name, "MCCWinStore-Win64-Shipping.exe")) {
			assert(false); // todo
			type = 1;
			offset_table = k_mcc_winstore_offset_table;
		} else if (strcmp(name, "MCC-Win64-Shipping.exe")) {
			MessageBox(NULL, TEXT("This mod won't be initialized."), TEXT("Invalid Game"), MB_OK);
			break;
		}

		// todo: initialize global memory

		// initialize global value
		g_mcc_global.type = type;
		g_mcc_global.instance = module;

		for (int i = 0; i < k_mcc_offset_count; ++i) {
			g_mcc_address_table[i] = reinterpret_cast<char*>(module) + offset_table[i];
		}

		// create window thread
		CreateThread(
			NULL, 
			NULL, 
			[](LPVOID lpThreadParameter) -> DWORD {return WinMain(NULL, NULL, NULL, NULL); }, 
			NULL, 
			NULL, 
			NULL
		);

		// setup second init
		auto m_UMCCGameInstanceInit = UMCCGameInstanceInit;
		auto p_UMCCGameInstanceInit = g_mcc_address_table[_mcc_offset_MCCGameInstance_vInit];
		g_UMCCGameInstanceInit = *reinterpret_cast<t_UMCCGameInstanceInit*>(p_UMCCGameInstanceInit);
		win32_write_memory(p_UMCCGameInstanceInit, &m_UMCCGameInstanceInit, sizeof(void*));
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

#include "win32helper.h"

#include <cassert>

void* 
win32_get_directory_entry(HMODULE hModule, int IMAGE_DIRECTORY_ENTRY_) {
	auto module = reinterpret_cast<char*>(hModule);
	auto pnth = reinterpret_cast<PIMAGE_NT_HEADERS>(module + reinterpret_cast<PIMAGE_DOS_HEADER>(hModule)->e_lfanew);
	return module + pnth->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_].VirtualAddress;
}

const char* 
win32_get_export_name(HMODULE hModule) {
	auto pExport = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(win32_get_directory_entry(hModule, IMAGE_DIRECTORY_ENTRY_EXPORT));
	return reinterpret_cast<const char*>(hModule) + pExport->Name;
}

s_version
win32_get_version(HMODULE hModule) {
	struct VERHEAD {
		WORD wTotLen;
		WORD wValLen;
		WORD wType;         /* always 0 */
		WCHAR szKey[(sizeof("VS_VERSION_INFO") + 3) & ~03];
		VS_FIXEDFILEINFO vsf;
	};

	auto hVerRes = FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), VS_FILE_INFO);

	assert(hVerRes);

	auto pVerHead = reinterpret_cast<VERHEAD*>(LoadResource(hModule, hVerRes));

	assert(pVerHead && pVerHead->vsf.dwSignature == 0xfeef04bd);

	return s_version {
		.major = HIWORD(pVerHead->vsf.dwFileDateMS),
		.minor = LOWORD(pVerHead->vsf.dwFileDateMS),
		.build = HIWORD(pVerHead->vsf.dwFileDateLS),
		.revision = LOWORD(pVerHead->vsf.dwFileDateLS),
	};
}

void win32_set_thread_name(const char* name) {
#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO {
		DWORD dwType;     // Must be 0x1000
		LPCSTR szName;    // Pointer to name (in user addr space)
		DWORD dwThreadID; // Thread ID (-1 for caller thread)
		DWORD dwFlags;    // Reserved for future use, must be zero
	} THREADNAME_INFO;
#pragma pack(pop)

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = name;
	info.dwThreadID = static_cast<DWORD>(-1);
	info.dwFlags = 0;

	__try {
		RaiseException(0x406D1388, 0, sizeof(info) / sizeof(ULONG_PTR), reinterpret_cast<ULONG_PTR*>(&info));
	} __except (EXCEPTION_EXECUTE_HANDLER) {}
}

void 
win32_write_memory(void* dst, void* src, size_t size) {
	DWORD old_protect;

	auto result = VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &old_protect);

	assert(("Failed to change protection", result));

	memcpy(dst, src, size);

	result = VirtualProtect(dst, size, old_protect, &old_protect);

	assert(("Failed to restore protection", result));
}

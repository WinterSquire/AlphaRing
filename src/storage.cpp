#include "storage.h"

#include <array>
#include <string>
#include <memory>
#include <format>
#include <cassert>
#include <Windows.h>

using string = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;

struct s_storage_global {
	string directorys[k_number_of_storage_directory];
};

static s_storage_global g_storage_global;

constexpr std::array<const TCHAR*, k_number_of_storage_directory> k_directory_path{
	TEXT(""),
	TEXT("config"),
	TEXT("profile"),
};

static std::unique_ptr<TCHAR[]>
win32_get_personal_directory() {
	HKEY hKey;

	auto status = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"),
		NULL,
		KEY_READ,
		&hKey
	);

	if (status != ERROR_SUCCESS) {
		return NULL;
	}

	std::unique_ptr<TCHAR[]> result;
	DWORD length = 0;

	for (int i = 0; i < 2; ++i) {
		if (i == 1) {
			result = std::make_unique<TCHAR[]>(length);
		}

		status = RegQueryValueEx(
			hKey,
			TEXT("Personal"),
			NULL,
			NULL,
			(LPBYTE)result.get(),
			&length
		);

		assert(status == ERROR_SUCCESS);
	}

	return result;
}

static int
win32_check_directory(const TCHAR* directory) {
	if (CreateDirectory(directory, NULL)) {
		return 0;
	}

	auto error = GetLastError();

	if (error != ERROR_ALREADY_EXISTS) {
		return error;
	}

	return 0;
}

int 
storage_initialize() {
	auto personal = win32_get_personal_directory();

	assert(personal != NULL);

	for (int i = 0; i < k_number_of_storage_directory; ++i) {
		// format directory path
		g_storage_global.directorys[i] = std::format(
			TEXT("{}\\{}\\{}"),
			personal.get(),
			TEXT("Alpha Ring"),
			k_directory_path[i]
		);

		win32_check_directory(g_storage_global.directorys[i].c_str());
	}

	return 0;
}

const wchar_t* 
storage_get_directory(int directory) {
	return g_storage_global.directorys[directory].c_str();
}

int 
storage_uninitialize() {
	return 0;
}

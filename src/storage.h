#pragma once

enum e_storage_directory {
	_storage_directory_root,
	_storage_directory_config,
	_storage_directory_profile,

	k_number_of_storage_directory
};

int
storage_initialize();

const wchar_t*
storage_get_directory(int directory);

int
storage_uninitialize();
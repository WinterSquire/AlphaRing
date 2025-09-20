#pragma once

#include "common.h"
#include <Windows.h>

void* 
win32_get_directory_entry(HMODULE hModule, int IMAGE_DIRECTORY_ENTRY_);

const char* 
win32_get_export_name(HMODULE hModule);

s_version
win32_get_version(HMODULE hModule);

void
win32_set_thread_name(const char* name);

void 
win32_write_memory(void* dst, void* src, size_t size);
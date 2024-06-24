#pragma once

#define MAX_PATH 260

namespace AlphaRing::Filesystem {
    bool Init();
    bool Shutdown();

    void GetDir(const char* path_in, wchar_t path_out[MAX_PATH]);
    void GetDir(const wchar_t* path_in, wchar_t path_out[MAX_PATH]);
    void GetResource(const char* path_in, wchar_t path_out[MAX_PATH]);
}
#include "Filesystem.h"

#include <filesystem>

bool AlphaRing::Filesystem::Init() {
    const char* home_dir = "../../../alpha_ring";

    if (!std::filesystem::exists(home_dir)) {
        std::filesystem::create_directories(home_dir);
    }

    return true;
}

bool AlphaRing::Filesystem::Shutdown() {
    return true;
}

void AlphaRing::Filesystem::GetDir(const wchar_t *path_in, wchar_t *path_out) {
    std::wcscpy(path_out, std::filesystem::absolute(path_in).c_str());
}

void AlphaRing::Filesystem::GetDir(const char *path_in, wchar_t *path_out) {
    std::wcscpy(path_out, std::filesystem::absolute(path_in).c_str());
}

void AlphaRing::Filesystem::GetResource(const char *path_in, wchar_t *path_out) {
    std::wcscpy(path_out,
                std::filesystem::absolute(std::filesystem::path("./alpha_ring").append(path_in)).c_str());
}

bool AlphaRing::Filesystem::Exist(const char *path) {
    return std::filesystem::exists(std::filesystem::path(path));
}

bool AlphaRing::Filesystem::Exist(const wchar_t *path) {
    return std::filesystem::exists(std::filesystem::path(path));
}

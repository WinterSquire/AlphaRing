#pragma once

struct s_version {
	unsigned short major, minor, build, revision;
};

constexpr s_version k_current_version{ 1,3495,0,0 };

inline bool is_equal(s_version* v1, s_version* v2) {
	return *reinterpret_cast<long long*>(v1) == *reinterpret_cast<long long*>(v2);
}
#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <libmcc/libmcc.h>

union s_version {
	struct { unsigned short major, minor, build, revision;  };
	unsigned long long ull;
};
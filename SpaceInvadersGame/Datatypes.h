#pragma once
#include <cassert>
#include <cstdint>
#include <climits>

static_assert(CHAR_BIT == 8, "Char's on this platform are not 8 bits wide.\n");
using char8_t = char;
using uchar8_t = unsigned char;
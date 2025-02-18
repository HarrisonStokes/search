#ifndef FLAGS_H
#define FLAGS_H

#include <iostream>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "flags.h"

namespace FLAG {
	extern const uint8_t QUIET;
	extern const uint8_t COLOR;
	extern const uint8_t CASE;
	extern const uint8_t RECUR;
	extern const uint8_t DIRM;
}

uint8_t set_flags(std::string flags);

#endif

#include <iostream>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <unordered_map>

namespace FLAG {
	const uint8_t QUIET	= 1;
	const uint8_t COLOR	= 2;
	const uint8_t CASE	= 4;
	const uint8_t RECUR	= 8;
	const uint8_t DIRM	= 16;
};

uint8_t set_flags(std::string flags) {
	const std::unordered_map<char, uint8_t> lookup {
		{'q', FLAG::QUIET},
		{'c', FLAG::COLOR},
		{'I', FLAG::CASE},
		{'R', FLAG::RECUR},
		{'d', FLAG::DIRM}
	};
	uint8_t flag_bitfield = 0;
	for(uint64_t idx = 0; idx < flags.length(); idx++) {
		char flag = flags[idx];
		try {
			uint8_t flag_bit = lookup.at(flag);
			flag_bitfield |= flag_bit;
		}
		catch(const std::out_of_range& ex) {
			std::cerr << "Ignoring invalid flag -" << flag << "\n";
		}
	}
	return flag_bitfield;
}

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

const uint8_t QUIETMASK = 1;
const uint8_t COLORMASK = 2;
const uint8_t CASEMASK = 4;
const uint8_t RECURMASK = 8;
const uint8_t DIRMASK = 16;

uint8_t set_flags(std::string flags) {
	const std::unordered_map<char, uint8_t> lookup {
		{'q', QUIETMASK},
		{'c', COLORMASK},
		{'I', CASEMASK},
		{'R', RECURMASK},
		{'d', DIRMASK}
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

#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <cstdint>
#include "Colors.h"

void search_file(std::ifstream source_file, std::ostream* output_stream, uint8_t flag_bitfield, std::string& pattern) {
	const std::string MATCHCOLOR = BOLDRED;
	std::string file_line = "";

	for(uint64_t lineno = 0; std::getline(source_file, file_line); lineno++) {
		std::string matching_line = "ln " + std::to_string(lineno) + ":\t\t";
		std::string matching_chars = "";
		bool match = false;
		uint64_t pattern_idx = 0;
		for(uint64_t line_idx = 0; line_idx < file_line.length(); line_idx++) {
			if(pattern_idx == pattern.length()) {
				match = true;
				if(flag_bitfield & FLAG::COLOR) 
					matching_line += MATCHCOLOR + matching_chars + RESET;
				else
					matching_line += matching_chars;
				
			}
			char pattern_char = pattern[pattern_idx];
			char file_char = file_line[line_idx];
			bool insensitive = flag_bitfield & FLAG::CASE;
			if((pattern_char | insensitive*0x20) == (file_char | insensitive*0x20)) {
				pattern_idx++;
				matching_chars += file_char;
			}
			else if(pattern_char == file_char) {
				pattern_idx++;
				matching_chars += file_char;
			}
			else {
				pattern_idx = 0;
				matching_line += matching_chars + file_char;
				matching_chars = "";
			}
		}
		if(match && !(flag_bitfield & FLAG::QUIET)) {
			*output_stream << matching_line << "\n";
		}
	}
}

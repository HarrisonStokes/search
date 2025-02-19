#include "../include/cmdline.h"

#define FLAG_START '-'
#define OUTPUT_START "-o"
#define INPUT_START "-i"

std::vector<std::string> get_cmdline_source(std::vector<std::string>& arguments) {
	std::vector<std::string> source_files;
	uint64_t start_idx = 0;
	uint64_t end_idx = 0;
	for(uint64_t idx = 0; idx < arguments.size(); idx++) {
		if(arguments[idx] == INPUT_START) {
			start_idx = idx;
		}
		else if(arguments[idx] == "-") {
			end_idx = idx-1;
			break;
		}
		else if(start_idx)
			source_files.push_back(arguments[idx]);
	}
	if(start_idx) {
		arguments.erase(arguments.begin()+start_idx, arguments.end()+end_idx);
	}
	return source_files;
}

std::string get_cmdline_flags(std::vector<std::string>& arguments) {
	std::string flags = "";
	for(uint64_t idx = 0; idx < arguments.size(); idx++) {
		flags = arguments[idx];
		if(flags[0] == FLAG_START && flags != OUTPUT_START) {
			flags.erase(0, 1);
			arguments.erase(arguments.begin() + idx);
			return flags;
		}
	}
	return "";
}

std::vector<std::string> get_cmdline_output(std::vector<std::string>& arguments) {
	std::vector<std::string> output_files;
	uint64_t start_idx = 0;
	uint64_t end_idx = 0;
	for(uint64_t idx = 0; idx < arguments.size(); idx++) {
		if(arguments[idx] == OUTPUT_START) {
			start_idx = idx;
		}
		else if(arguments[idx] == "-") {
			end_idx = idx-1;
			break;
		}
		else if(start_idx)
			output_files.push_back(arguments[idx]);
	}
	if(start_idx) {
		arguments.erase(arguments.begin()+start_idx, arguments.end()+end_idx);
	}
	return output_files;
}


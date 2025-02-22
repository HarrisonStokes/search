#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include "include/common.h"

/*
 	Format:
	Without config:
		./way [source files] [-flags] [-o destination files]
	With config:
		./way [source files]

*/

static std::vector<std::string> vectorized(int argc, char** argv);
static void process_inputs(std::vector<std::string>& arguments, std::string& flags, std::vector<std::string>& source_files, std::vector<std::string>& output_files);
static std::ostream& set_output(std::vector<std::string>& output_files);

void print(std::vector<std::string> v) {
	for(uint64_t idx = 0; idx < v.size(); idx++) {
		std::cout << "Idx " << idx << ": " << v[idx] << "\n";
	}
}

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << "Error: Missing file to search\n";
		return -1;
	}
	std::vector<std::string> arguments, source_files, output_files;
	std::string flags = "";

	arguments = vectorized(argc, argv);
	process_inputs(arguments, flags, source_files, output_files);
	uint8_t flag_bitfield = set_flags(flags);
	std::ostream& output_stream = set_output(output_files);
	std::vector<std::string>& patterns = arguments;

	for(uint64_t source_idx = 0; source_idx < source_files.size(); source_idx++) {
		std::ifstream source(source_files[source_idx]);
		for(uint64_t pattern_idx = 0; pattern_idx < patterns.size(); pattern_idx++) {
			std::string pattern = patterns[pattern_idx];
			std::string message = source_files[source_idx] + ":\t" + RESET + pattern + "\n";
			output_stream << message;
			search_file(source, &output_stream, flag_bitfield, pattern);
			source.clear();
			source.seekg(0, std::ios::beg);
		}
		source.close();
	}
}

std::vector<std::string> vectorized(int argc, char** argv) {
	std::vector<std::string> arguments;
	for(int idx = 1; idx < argc; idx++)
		arguments.push_back(argv[idx]);
	return arguments;
}

void process_inputs(std::vector<std::string>& arguments,
					std::string& flags,
					std::vector<std::string>& source_files,
					std::vector<std::string>& output_files) {
	flags = get_cmdline_flags(arguments);
	output_files = get_cmdline_output(arguments);
	source_files = get_cmdline_source(arguments); // Note this has to be last as sources files do not have a check
	if(source_files.empty()) {
		std::cerr << "Error: Missing files to search\n";
		return;
	}
	if(arguments.empty()) {
		std::cerr << "Error: Missing keywords to search";
		return;
	}
	if(flags == "" && output_files.empty()) {
		arguments = process_config();
		std::pair<int, std::pair<uint64_t, uint64_t>> valid = validate_config(arguments);
		switch(valid.first) {
			case  ERR_CONFIG_MISSING_KEYS:
				break;
			case ERR_CONFIG_INVALID_NAME:
				break;
			case ERR_CONFIG_TOO_MANY_KEYS:
				break;
		}
		std::pair<uint64_t, uint64_t> indexes = valid.second;
		flags = get_config_flags(arguments, indexes); 
		output_files = get_config_output(arguments, indexes);
		std::cout << "Flags:\t" << flags << "\n";
		std::cout << "Input Files:\n";
		print(source_files);
		std::cout << "Output Files:\n";
		print(output_files);
	}
}

std::ostream& set_output(std::vector<std::string>& output_files) {
	if(output_files.empty())
		return std::cout;
	static std::ofstream file_output(output_files[0]);
	return file_output;
}

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>
#include <deque>
#include <unordered_map>
#include <cctype>
#include "Colors.h"

/*
 	Compile:
		g++ searcher.cc -std=c++17 -o search
 	To use:
		./search  [source_file1 ... source_fileN] -FLAGS [-o dest_file1 ... -o dest_fileN]
									or
		./search [starting_path] -R(FLAGS) [-o dest_file1 ... -o dest_fileN]

	Note:
		Every destination file MUST be preceeded with a -o
	
	Flags are:
		-q = quiet				, doesn't print (To be expounded upon latter).
		-c = color				, highlights character sequence that matches pattern.
		-i = case insensitivity	, ignores cases. 
		-R = recursive search	, recursively searches from starting path
		-d = searches directory , searches through a directory
 */

std::string MATCHCOLOR = BOLDRED;
std::string DIRCOLOR = BOLDBLUE;
const std::string ERRHEADER = BOLDRED + "E" + RESET + ":\t";
const std::string WARNHEADER = BOLDMAGENTA + "W" + RESET + ":\t";
const std::string OUTPUTFLAG = "-o";
const uint8_t QUIETMASK = 1; 
const uint8_t COLORMASK = 2;
const uint8_t CASEMASK = 4;
const uint8_t RECURMASK = 8;
const uint8_t DIRMASK = 16;

uint8_t FLAG_BITFIELD = 0;
const std::unordered_map<char, uint8_t> flag_lookup = {
	{'q', QUIETMASK},
	{'c', COLORMASK},
	{'i', CASEMASK},
	{'R', RECURMASK},
	{'d', DIRMASK}
};

std::deque<std::string> parse_flags(int argc, char** argv, std::vector<uint8_t>& nonflag_idxs, uint8_t& flag_idx) {
	std::deque<std::string> flags;
	flag_idx = 0;
	for(uint8_t idx = 1; idx < argc; idx++) {
		if(strcmp(argv[idx], "-o") == 0) {
			if(idx+1 >= argc) {
				std::cerr << ERRHEADER<< "-o is missing destination";
				exit(1);
			}
			flags.push_front(std::string(argv[idx+1]));
			flags.push_front(OUTPUTFLAG);
			flag_idx += 2;
		}
		else if(argv[idx][0] == '-') { 
			flags.push_back(argv[idx]);	
		}
		else {
			nonflag_idxs.push_back(idx);
		}
	}
	return flags;
}

std::vector<std::string> parse_source_files(int argc, char** argv, std::vector<uint8_t>& nonflag_idxs, std::vector<std::string>& patterns, std::vector<std::string>& start_paths) {
	if(nonflag_idxs.size() < 1) {
		std::cerr << ERRHEADER << "Missing source files and pattern." << std::endl;
		exit(1);
	}
	std::vector<std::string> source_files;
	for(uint64_t idx = 0; idx < nonflag_idxs.size(); idx++) {
		std::string arg = argv[nonflag_idxs[idx]];
		if(std::filesystem::exists(arg) && std::filesystem::is_regular_file(arg)) {
			source_files.push_back(arg);
		}
		//else if(std::filesystem::exists(arg) && std::file(arg)) {
		//	start_paths.push_back(arg);
		//}
		else if((std::filesystem::exists(arg) && std::filesystem::is_regular_file(arg) == false)) {
			std::cerr << ERRHEADER << arg << " - is a directory." << std::endl; 
			exit(1);
		}
		else {
			patterns.push_back(arg);
		}
	}
	if(!patterns.size()) {
		std::cerr << ERRHEADER << "Missing pattern to search for." << std::endl;
		exit(1);
	}
	return source_files;
}

void set_flags(std::deque<std::string> flags, uint8_t flag_idx) {
	for(uint8_t flags_idx = flag_idx; flags_idx < flags.size(); flags_idx++) {
		for(uint64_t idx = 1; idx < flags[flags_idx].size(); idx++) {
			char flag = flags[flags_idx][idx];
			try {
				uint8_t bitmask = flag_lookup.at(flag);
				FLAG_BITFIELD |= bitmask;
			} 
			catch(const std::out_of_range& ex) {
				std::cerr << WARNHEADER << "Ignoring invalid flag -" << flag << "\n";
			}
		}
	}
}

std::deque<std::string> procress_config(std::ifstream& config, uint8_t& flag_idx) {
	std::deque<std::string> flags;
	flag_idx = 0;
	std::string line = "";
	while(config >> line){
		if(line  == "-o") {
			config >> line;
			if(config.eof() == true) {
				std::cerr << ERRHEADER<< "-o is missing destination in config file";
				exit(1);
			}
			flags.push_front(std::string(line));
			flags.push_front(OUTPUTFLAG);
			flag_idx += 2;
		}
		else if(line[0] == '-') { 
			flags.push_back(line);	
		}
	}
	return flags;
}

void gather_source_files(std::vector<std::string> source_files, std::string start_path) {
	
}

std::string tolower_str(std::string word) {
	for(uint16_t idx = 0; idx < word.length(); idx++) {
		word[idx] = word[idx] | 0b0010'0000;
	}
	return word;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << ERRHEADER << "Missing parameter(s)." << std::endl;
		exit(1);
	}
	// Parsing
	std::vector<uint8_t> nonflag_idxs;
	uint8_t flag_idx = 0;
	std::deque<std::string> flags = parse_flags(argc, argv, nonflag_idxs, flag_idx);

	if(flags.size() == 0) {
		std::ifstream config_file("~/C++/Searcher/search.config");
		flags = procress_config(config_file, flag_idx);
		config_file.close();
	}
	set_flags(flags, flag_idx);

	std::vector<std::string> patterns;
	std::vector<std::string> start_paths;
	std::vector<std::string> source_files = parse_source_files(argc, argv, nonflag_idxs, patterns, start_paths);
	
	if(FLAG_BITFIELD & RECURMASK) {
		if(start_paths.size() != 0) {
			for(uint16_t idx = 0; idx < start_paths.size(); idx++) {
				gather_source_files(source_files, start_paths[idx]);
			}
		}
		else if(source_files.size() != 0) {
			std::cerr << WARNHEADER << " -R is enabled but missing starting directory.\n";
		}
		else {
			std::cerr << ERRHEADER << " -R is enabled but missing starting directory." << std::endl;
		}
	}

	std::ostream* output_stream = nullptr;
	if(flags[0] == OUTPUTFLAG) {
		output_stream = new std::ofstream(flags[1]);
	}
	else {
		output_stream = &std::cout;
	}
	// Core Logic
	for(uint64_t file_idx = 0; file_idx < source_files.size(); file_idx++) {				// Source Files
		std::ifstream source_file(source_files[file_idx]);
		for(uint64_t patterns_idx = 0; patterns_idx < patterns.size(); patterns_idx++) {	// Patterns
			std::string message = source_files[file_idx] + ":\t" + RESET+ patterns[patterns_idx];
			if(FLAG_BITFIELD & COLORMASK) {
				message = "\n" + DIRCOLOR + message;
			}
			message = UNDERLINE + message;
			if(!(FLAG_BITFIELD & QUIETMASK)) {
				*output_stream << message << "\n";
			}
			std::string pattern = patterns[patterns_idx];
			if(FLAG_BITFIELD & CASEMASK) {
				pattern = tolower_str(pattern);
			}
			std::string file_line = "";
			for(uint64_t lineno = 0; getline(source_file, file_line); lineno++) {			// Source Files Lines
				std::string matching_line = "ln " + std::to_string(lineno) + ":\t\t";
				std::string matching_chars = "";
				bool match = false;
				uint64_t pattern_idx = 0;
				for(uint64_t line_idx = 0; line_idx < file_line.length(); line_idx++) {		// Search line
					if(pattern_idx == pattern.length()) {
						match = true;
						if(FLAG_BITFIELD & COLORMASK) {
							matching_line += MATCHCOLOR + matching_chars + RESET;
						}
						else {
							matching_line += matching_chars;
						}
						pattern_idx = 0;
						matching_chars = "";
					}
					if((FLAG_BITFIELD & CASEMASK) && pattern[pattern_idx] == (file_line[line_idx] | 0b0010'0000)) {
						pattern_idx++;
						matching_chars += file_line[line_idx];
					}
					else if(file_line[line_idx] == pattern[pattern_idx]) {
						pattern_idx++;
						matching_chars += file_line[line_idx];
					}
					else {
						pattern_idx = 0;
						matching_line += matching_chars + file_line[line_idx];
						matching_chars = "";
					}
				}
				if(match && !(FLAG_BITFIELD & QUIETMASK)) {																	// Print matching line
					*output_stream << matching_line << "\n";
				}
			}
			source_file.clear();						// Removes error flags
			source_file.seekg(0, std::ios::beg);		// Resets file pointer
		}
		source_file.close();
	}
	if(flags[0] == OUTPUTFLAG) {
		delete output_stream;
		std::ifstream original(flags[1]);
		for(uint8_t file_idx = 3; file_idx < flag_idx; file_idx += 2) {
			std::ofstream copy_file(flags[file_idx]);
			std::string file_line = "";
			while(getline(original, file_line)) {
				copy_file << file_line << "\n";
			}
			original.clear();						// Removes error flags
			original.seekg(0, std::ios::beg);		// Resets file pointer
		}
	}
	exit(0);
}

#include "../include/config.h"

std::vector<std::string> process_config() {
	constexpr uint8_t lowercase_bit = 0x20;
	std::ifstream file(CONFIG_PATH);
	std::string line = "";
	std::vector<std::string> options;
	uint8_t key_count = 0;
	while(getline(file, line)) {
		if(line.length() < 2)
			continue;
		std::string word = "";
		for(uint16_t idx = 0; idx < line.length(); idx++) {
			char letter = line[idx];
			if(letter >= 'A' || letter <= 'Z')
				letter |= lowercase_bit;
			if(key_count > 3) {
				break;									// FIXME Will cause an unexplained error. It will delete the rest of the json keys and it will throw an error in validate_config() without describing the root error.
			}
			if(line[idx] == ',') {
				options.push_back(word);
			}
			else if(line[idx] == ':') {
				key_count++;
			}
			else if(letter <= 'z' && letter >= 'a') {
				word += letter;
			}
			else if(word.length() != 0) {
				options.push_back(word);
			}
			else {
				word = "";
			}
		}
		if(word.length() != 0 && options[options.size()-1] != word) {
			options.push_back(word);
		}
	}
	return options;
}

std::pair<int, std::pair<uint64_t, uint64_t>> validate_config(std::vector<std::string>& options) {
	if(options.size() < 4) {
		return {ERR_CONFIG_MISSING_KEYS, {ERR_CONFIG_MISSING_KEYS, ERR_CONFIG_MISSING_KEYS}};
	}
	if("default" != options[0]) {
		return {ERR_CONFIG_INVALID_NAME, {ERR_CONFIG_INVALID_NAME, ERR_CONFIG_INVALID_NAME}};
	}

	std::pair<uint64_t, uint64_t> indexes;
	bool output_exist = 0;
	bool flag_exist = 0;
	for(uint64_t idx = 1; idx < options.size(); idx++) {
		if(options[idx] == CONFIG_OUTPUT_KEY) {
			if(output_exist)
				return {ERR_CONFIG_TOO_MANY_KEYS, {ERR_CONFIG_TOO_MANY_KEYS, ERR_CONFIG_TOO_MANY_KEYS}};
			output_exist = !output_exist;
			indexes.second = idx+1;
		}
		if(options[idx] == CONFIG_FLAG_KEY) {
			if(flag_exist)
				return {ERR_CONFIG_TOO_MANY_KEYS, {ERR_CONFIG_TOO_MANY_KEYS, ERR_CONFIG_TOO_MANY_KEYS}};
			flag_exist = !flag_exist;
			indexes.first = idx+1;
		}
	}
	return {0, indexes};
}

std::string get_config_flags(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index) {
	std::string flags = "";
	uint64_t end = index.second;
	if(end < index.first)
		end = options.size();
	for(uint64_t idx = index.second; idx < end; idx++) {
		flags += options[idx];
	}
	return flags;
}
std::vector<std::string> get_config_output(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index) {
	std::vector<std::string> output_paths;
	uint64_t end = index.first;
	if(end < index.second)
		end = options.size();
	for(uint64_t idx = index.second; idx < end; idx++) {
		output_paths.push_back(options[idx]);
	}
	return output_paths;
}

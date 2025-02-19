#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

#define CONFIG_PATH "config.json"
#define CONFIG_OUTPUT_KEY "OUTPUTS"
#define CONFIG_FLAG_KEY "FLAGS"
#define ERR_CONFIG_MISSING_KEYS -1
#define ERR_CONFIG_INVALID_NAME -2
#define ERR_CONFIG_TOO_MANY_KEYS -3

std::vector<std::string> process_config();

std::pair<int, std::pair<uint64_t, uint64_t>> validate_config(std::vector<std::string>& options);

std::string get_config_flags(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index);

std::vector<std::string> get_config_output(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index);

#endif

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

std::vector<std::string> process_config();

std::pair<int, std::pair<uint64_t, uint64_t>> validate_config(std::vector<std::string>& options);

std::string get_config_flags(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index);

std::vector<std::string> get_config_output(std::vector<std::string>& options, std::pair<uint64_t, uint64_t>& index);

#endif

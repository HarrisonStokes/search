#ifndef CMDLINE_H
#define CMDLINE_H

#include <string>
#include <vector>
#include <cstdint>

std::vector<std::string> get_source_files(std::vector<std::string>& arguments);
std::string get_cmdline_flags(std::vector<std::string>& arguments);
std::vector<std::string> get_cmdline_output(std::vector<std::string>& arguments);


#endif

#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <cstdint>
#include "colors.h"
#include "flags.h"

void search_file(std::ifstream& source, std::ostream* output, const uint8_t& flags, const std::string& pattern);

#endif

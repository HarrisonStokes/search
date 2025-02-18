#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <cstdint>
#include "colors.h"
#include "flags.h"

void search_file(std::ifstream source_file, std::ostream* output_stream, uint8_t flag_bitfield, std::string& pattern);

#endif

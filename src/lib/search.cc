#include "../include/search.h"


std::vector<int> generateTable(const std::string& pattern) {
	std::vector<int> charTable(256,-1);
	for(uint64_t idx = 0; idx < pattern.length(); idx++) {
		charTable[pattern[idx]] = idx;
	}
	return charTable;
}

std::vector<int> boyerMooreSearch(const std::vector<int>& charTable, const std::string& text, const std::string pattern) {
	std::vector<int> occurences;
	int64_t text_length = text.length();
	int64_t pattern_length = pattern.length();
	if(pattern_length > text_length) 
		return occurences;

	int text_idx = 0;
	while(text_idx <= (text_length-pattern_length)) {
		int pattern_idx = pattern_length-1;
		while(pattern_idx >= 0 && pattern[pattern_idx] == text[text_idx+pattern_idx]) {
			pattern_idx--;
		}
		if(pattern_idx < 0) {
			occurences.push_back(text_idx);
			text_idx += (text_idx+pattern_idx < text_length) ? pattern_idx-charTable[text[text_idx+pattern_idx]] : 1;
		}
		else {
			text_idx += std::max(1, pattern_idx-charTable[text[text_idx+pattern_idx]]);
		}
	}
	return occurences;
}

std::string build_message(const uint8_t& flags, std::vector<int>& occurences, const std::string& line, const int64_t pattern_length) {
	const std::string MATCHCOLOR = BOLDRED;
	std::string message = "";
	int64_t pattern_idx = 0;
	int64_t line_length = line.length();
	int64_t occurence_length = line.length();
	for(int64_t idx = 0; idx < line_length; idx++) {
		bool lower_bound = idx >= occurences[pattern_idx];
		bool upper_bound = idx <= occurences[pattern_idx]-pattern_length;
		if(flags & FLAG::COLOR && lower_bound && upper_bound) {
			message += MATCHCOLOR + line[idx] + RESET;
		}
		else {
			message += line[idx];
		}
		if(idx >= occurences[pattern_idx+1] && occurence_length < pattern_idx+1) {
			pattern_idx++;
		}
	}
	return message;
}

void search_file(std::ifstream& source, std::ostream* output, const uint8_t& flags, const std::string& pattern) {
	std::vector<int> charTable = generateTable(pattern);
	std::string line = "";

	for(uint64_t lineno = 0; std::getline(source, line); lineno++) {
		std::vector<int> occurences = boyerMooreSearch(charTable, line, pattern);
		std::cout << line << "\n";
		if(occurences.empty())
			continue;
		*output << "ln" << lineno << ":\t\t" << build_message(flags, occurences, line, pattern.length());
	}
}

/*
 STRING SEARCHING ALGORITHMS:

	Knuth-Morris-Pratt (KMP):
		How it works:
			* It utilizes a an array that stores the longest proper prefix. 
			* The array, LPS, is used when an mismatch occurs and it indicates how much of the pattern can be reused.

		LPS Array:
			* A proper prefix is a prefix that doesn't include the whole string.
			  The suffixes is the remaing portions of the string after the prefixes.
			* Each elment in LPS is the length of the longest proper prefix of pattern[0..i].

		Conditions:
			Case 1: pattern[i] = pattern[len]
				* Extend the LPS at the previous index, we can increment by 1 and store its value at lps[i].

			Case 2: pattern[i] != pattern[len] and len = 0:
				* No matching character earlier and current characters are not matching, lps[i] = 0.

			Case 3: pattern[i] != [attern[len] and len > 0:
				* LPS cannot be extended at index i.
				* There can be a smaller prefix that matches the suffix ending at i.
				* Look for a smaller suffx of pattern[i-len-1].
				* The match pattern[i] with the next character of this prefix.
				* If pattern[i] = length of matching prefix, theres are match.
				* Since lps[i-1] == len, pattern[0..len-1] == pattern[i-len..i-1], therefore we can use lps[len-1] to update len.

		Time Complexity:
			* Preprocessing: O(m) m = pattern length
			* Searching: O(n) n = text length
			* Overal: O(n + m)
		
		When to use:
			When frequent matches are expected.
	
	Boyer-Moore (BM):
		How it works:

		Time Complexity:
			* Best case: O(n/m)
			* Average case: O(n)
			* Worst case: O(nm)

		When to use:
			When frequent matches are expected.
*/

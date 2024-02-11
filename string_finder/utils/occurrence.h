#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <unordered_map>
#include <vector>
#include <cstdint>


typedef struct Occurrence {
	size_t at_index{};

	std::string prefix;

	std::string suffix;

	std::string file;

	Occurrence(size_t at_index, std::string prefix, std::string suffix, std::string file);
	static void print(const Occurrence& occurrence);
} Occurrence;

void delete_bad_match_table(std::unordered_map<char, int>* bad_match_table);
void find_occurrences(std::vector<Occurrence>* occurrences, const std::unordered_map<char, int>* bad_match_table,
		const std::string& needle, const std::string& haystack);
std::unordered_map<char, int>* create_bad_match_table(const std::string& needle);
void
insert_pair_bad_match_table(uint8_t needle_len, std::unordered_map<char, int>* bad_match_table, uint8_t needle_index,
		char character_to_find);
uint8_t
calc_shift(const std::unordered_map<char, int>* bad_match_table, size_t needle_end_index, const std::string& haystack);

Occurrence create_occurrence(const std::string& haystack, size_t needle_end_index, const std::string& needle);

#endif //STRING_FINDER_OCCURRENCE_H

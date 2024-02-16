#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <unordered_map>
#include <vector>
#include <cstdint>

#include "file.h"
#include "err.h"


class Occurrence {
public:
    Occurrence(size_t at_index, std::string prefix, std::string suffix, std::string file)
            : at_index(at_index), prefix(std::move(prefix)), suffix(std::move(suffix)), file(std::move(file)) {}

    void print() const {
        std::cout << file << "(" << at_index << "):" << prefix << "..." << suffix << "\n";
    }

private:
    size_t at_index;
    std::string prefix, suffix, file;
};

std::unique_ptr<std::unordered_map<char, int>> create_bad_match_table(const std::string& needle);

void find_occurrences(std::vector<Occurrence>* occurrences, std::vector<fs::path>* files, const std::unordered_map<char, int>* bad_match_table,
		const std::string& needle);
void
insert_pair_bad_match_table(uint8_t needle_len, std::unique_ptr<std::unordered_map<char, int>>& bad_match_table, uint8_t needle_index,
		char character_to_find);
uint8_t
calc_shift(const std::unordered_map<char, int>* bad_match_table, size_t needle_end_index, const std::string& haystack);

Occurrence create_occurrence(const std::string& haystack, size_t needle_end_index, const std::string& needle, fs::path path);

#endif //STRING_FINDER_OCCURRENCE_H

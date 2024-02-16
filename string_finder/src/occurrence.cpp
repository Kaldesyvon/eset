#include <iostream>
#include <string>


#include "../include/occurrence.h"


std::unique_ptr<std::unordered_map<char, int>> create_bad_match_table(const std::string& needle)
{
	uint8_t needle_len = needle.length();
    auto bad_match_table = std::make_unique<std::unordered_map<char, int>>();

	for (uint8_t needle_index = 0; needle_index < needle_len; needle_index++) {
		char character_to_find = needle[needle_index];

		insert_pair_bad_match_table(needle_len, bad_match_table, needle_index, character_to_find);
	}
	bad_match_table->insert({ '*', needle_len });

	return bad_match_table;
}

void
insert_pair_bad_match_table(uint8_t needle_len, std::unique_ptr<std::unordered_map<char, int>>& bad_match_table, uint8_t needle_index,
		char character_to_find)
{
	bool is_last_char = (needle_index == needle_len - 1);

	auto occurrence = bad_match_table->find(character_to_find);

	if (!is_last_char || (occurrence == bad_match_table->end())) {
		int shift_value = is_last_char ? static_cast<int>(needle_len) : std::max(1,
				static_cast<int>(needle_len - needle_index - 1));

		(*bad_match_table)[character_to_find] = shift_value;
	}
}

void find_occurrences(std::vector<Occurrence>* occurrences, std::vector<fs::path>* files, const std::unordered_map<char, int>* bad_match_table,
		const std::string& needle)
{
    // tu bude files vector a z neho si tato funckia bude brat fily.
    for (const fs::path& path : *files) {
        auto [haystack, haystack_len] = get_file_content(path.c_str());

        uint8_t needle_len = needle.length();

        uint8_t needle_last_char_index = needle_len - 1;

        size_t haystack_index = needle_last_char_index;

        while (haystack_index < haystack_len) {
            int needle_index = needle_last_char_index;
            size_t match_index = haystack_index - needle_last_char_index;

            while (needle_index >= 0 && needle[needle_index] == haystack[match_index + needle_index]) {
                needle_index--;
            }
            if (needle_index < 0) {
                Occurrence occurrence = create_occurrence(haystack, haystack_index, needle, path);
                occurrences->push_back(occurrence);
                haystack_index += needle_len;
            }
            else {
                uint8_t shift = calc_shift(bad_match_table, haystack_index, haystack);
                haystack_index += shift;
            }
        }

        munmap(haystack, haystack_len);
    }
}

std::string transform_escape_seq(char prefix_char)
{
	if (prefix_char == '\t') {
		return "\\t";
	}
	else if (prefix_char == '\n') {
		return "\\n";
	}
	return std::string(1, prefix_char); // NOLINT(*-return-braced-init-list)
}

std::string create_prefix(const std::string& haystack, size_t needle_end_index, uint8_t needle_len)
{
	std::string prefix;

	size_t needle_start_index = needle_end_index - (needle_len - 1);

	uint8_t prefix_len = (uint8_t)std::min(static_cast<size_t>(3), needle_start_index);

	size_t prefix_start = needle_start_index - prefix_len;

	for (uint8_t prefix_inc = 0; prefix_inc < prefix_len; prefix_inc++) {
		char prefix_char = haystack[prefix_start + prefix_inc];
		prefix += transform_escape_seq(prefix_char);
	}

	return prefix;
}

std::string create_suffix(const std::string& haystack, size_t needle_end_index)
{
	std::string suffix;

	size_t haystack_len = haystack.length();

	uint8_t suffix_len = (uint8_t)std::min(static_cast<size_t>(3), haystack_len - needle_end_index);

	for (size_t suffix_inc = needle_end_index + 1; suffix_inc <= needle_end_index + suffix_len; suffix_inc++) {
		char suffix_char = haystack[suffix_inc];

		suffix += transform_escape_seq(suffix_char);
	}

	return suffix;
}

Occurrence create_occurrence(const std::string& haystack, size_t needle_end_index, const std::string& needle, fs::path path)
{
	std::string prefix = create_prefix(haystack, needle_end_index, needle.length());
	std::string suffix = create_suffix(haystack, needle_end_index);

	return {needle_end_index, prefix, suffix, path.filename().string() };
}

uint8_t
calc_shift(const std::unordered_map<char, int>* bad_match_table, size_t needle_end_index, const std::string& haystack)
{
	char bad_char = haystack[needle_end_index];
	return bad_match_table->at(bad_match_table->find(bad_char) != bad_match_table->end() ? bad_char : '*');
}

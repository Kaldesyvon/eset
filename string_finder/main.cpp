#include <unordered_map>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>

#include "utils/occurrence.h"


namespace fs = boost::filesystem;

void find_txt_files(const fs::path& root, std::vector<fs::path>& txt_files)
{
	if (!fs::exists(root) || !fs::is_directory(root)) return;   

	fs::recursive_directory_iterator it(root), end;

	while (it != end) {
		if (fs::is_regular_file(*it) && it->path().extension() == ".txt") {
			txt_files.push_back(it->path());
		}
		++it;
	}
}

int main(int argc, char* argv[])
{
	std::string to_find = "before";
	//    std::string to_find;
	//    to_find.reserve(128);

	std::string sentence = "afsdfafsdbeforeadsfsda";

	std::vector<fs::path> txt_files;
	fs::path root_path = "../text/";

	find_txt_files(root_path, txt_files);

	for (const auto& txt_file : txt_files)
		std::cout << txt_file.string();

	std::unordered_map<char, int>* bad_match_table = create_bad_match_table(to_find);

	std::vector<Occurrence> occurrences;

	find_occurrences(&occurrences, bad_match_table, to_find, sentence);

	for (const auto& occurrence : occurrences)
		Occurrence::print(occurrence);

	delete_bad_match_table(bad_match_table);

	return 0;
}

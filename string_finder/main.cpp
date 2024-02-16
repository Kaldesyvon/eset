#include <vector>
#include <iostream>

#include "include/occurrence.h"


void handle_user_input(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    try {
        handle_user_input(argc, argv);

        std::string to_find(argv[2]);
        fs::path root_path((std::string(argv[1])));
        std::vector<fs::path> txt_files;

        find_txt_files(root_path, txt_files);

        auto bad_match_table = create_bad_match_table(to_find);

        std::vector<Occurrence> occurrences;

        find_occurrences(&occurrences, &txt_files, bad_match_table.get(), to_find);

        for (const auto& occurrence : occurrences)
            occurrence.print();


        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}

void handle_user_input(int argc, char* argv[]) {
    if (argc < 3) throw std::runtime_error("less than 3 arguments provided.");
    if (argc > 3) throw std::runtime_error("more than 3 arguments provided.");
    if (std::string(argv[2]).length() > 128) throw std::runtime_error("string to find is longer than 128 characters.");
}

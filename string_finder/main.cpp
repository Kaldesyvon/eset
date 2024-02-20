#include <vector>
#include <iostream>

#include "include/File.h"

#define FILE_EXTENSION ".txt"


void handleUserInput(int argc, char* argv[]);
std::vector<std::unique_ptr<File>> findTxtFiles(const fs::path& root);

int main(int argc, char* argv[])
{
    try {
        handleUserInput(argc, argv);

        const std::string toFind(argv[2]);
        const fs::path rootPath((std::string(argv[1])));

        auto txtFiles = findTxtFiles(rootPath);

        // TODO: use raii and make it shared/unique
        const BadMatchTable badMatchTable(toFind);

        for (const auto& txtFile : txtFiles)
            txtFile->findOccurrences(badMatchTable, toFind);

        for (const auto& txtFile : txtFiles)
            txtFile->printOccurrences();


        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}

void handleUserInput(const int argc, char* argv[]) {
    if (argc < 3) throw std::runtime_error("less than 3 arguments provided. Usage: ./string_finder <path|file.txt> <string_to_find>");
    if (argc > 3) throw std::runtime_error("more than 3 arguments provided. Usage: ./string_finder <path|file.txt> <string_to_find>");
    if (std::string(argv[2]).length() > 128) throw std::runtime_error("string to find is longer than 128 characters.");
}

std::vector<std::unique_ptr<File>> findTxtFiles(const fs::path& root)
{
    // TODO: maybe try to check right for dirs
    if (!fs::exists(root))
        throw std::runtime_error(root.string() + " does not exists.");

    if (!fs::is_directory(root) && fs::extension(root) != FILE_EXTENSION)
        throw std::runtime_error(root.string() + " is neither .txt file nor directory.");

    std::vector<std::unique_ptr<File>> txtFiles;

    if(fs::extension(root) == ".txt") {
        txtFiles.push_back(std::make_unique<File>(root));
        return txtFiles;
    }

    fs::recursive_directory_iterator iterator(root), end;

    while (iterator != end) {
        if (fs::is_regular_file(*iterator) && iterator->path().extension() == ".txt") {
            txtFiles.push_back(std::make_unique<File>(iterator->path()));
        }
        iterator++;
    }

    return txtFiles;
}

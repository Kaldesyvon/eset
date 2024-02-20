#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "include/File.h"

#define FILE_EXTENSION ".txt"

/*
 * Function handles if user uses program incorrectly
 */
void handleUserInput(int argc, char* argv[]);
/*
 * Functions takes user's argument and finds all .txt files if any
 *
 * Argument which function asks is user's input path to dir/.txt file
 */
std::vector<std::unique_ptr<File>> findTxtFiles(const fs::path& root);
/*
 * This function acts as a wrapper for usage of multithreading
 */
void searchInFile(std::unique_ptr<File>& file, const std::shared_ptr<BadMatchTable>& badMatchTable, const std::string& needle);

/*
 * This program finds strings and its prefix and suffix in .txt files.
 * Program uses Boyer-Moore algorithm to find it effectively.
 * Program also uses multithreading, where for each file thread is created.
 * For understanding: haystack means file's content and needle means string to find. As we were finding needle in haystack :)
 * Program was developed by Martin Novysedlak in 2.2024 in Clion on Pop_OS! operating system for Eset challenge: https://join.eset.com/en/challenges/c-developer
 * Prerequisites: boost >= 1.74, c++ >= c++14.
 * Usage: ./string_finder <path | file.txt> <string to find>
 * TODO: Limitations
 */
int main(int argc, char* argv[])
{
    try {
        handleUserInput(argc, argv);

        const std::string needle(argv[2]);
        const fs::path rootPath((std::string(argv[1])));

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        auto txtFiles = findTxtFiles(rootPath);

        const auto badMatchTable = std::make_shared<BadMatchTable>(needle);

        std::vector<std::thread> threads;

        for (auto& file : txtFiles)
            threads.emplace_back(searchInFile, std::ref(file), std::ref(badMatchTable), needle);

        for (auto& thread : threads) {
            if (thread.joinable())
                thread.join();
        }

        const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Program finding duration: = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

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

    if (txtFiles.empty())
        throw std::runtime_error("no .txt files found.");

    return txtFiles;
}

void searchInFile(std::unique_ptr<File>& file, const std::shared_ptr<BadMatchTable>& badMatchTable, const std::string& needle) {
    file->findOccurrences(badMatchTable, needle);
}

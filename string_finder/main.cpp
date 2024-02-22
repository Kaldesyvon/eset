#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "include/File.h"

#define FILE_EXTENSION ".txt"
#define MULTITHREAD

/*
 * Function handles if user uses program incorrectly
 */
void handleUserInput(int argc, char *argv[]);

/*
 * This function acts as a wrapper for usage of multithreading
 */
void searchInFile(std::unique_ptr<File> &file, const std::shared_ptr<BadMatchTable> &badMatchTable,
                  const std::string &needle);


int main(int argc, char *argv[]) {
    try {
        handleUserInput(argc, argv);

        const std::string needle(argv[2]);
        const fs::path rootPath((std::string(argv[1])));

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        auto txtFiles = File::findTxtFiles(rootPath);

        const auto badMatchTable = std::make_shared<BadMatchTable>(needle);


#ifdef MULTITHREAD
        std::vector<std::thread> threads;

        for (auto &file: txtFiles)
            threads.emplace_back(searchInFile, std::ref(file), std::ref(badMatchTable), needle);

        for (auto &thread: threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
#else
        for (const auto& file : txtFiles) {
            file->findOccurrences(badMatchTable, needle);
        }
#endif

        const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Program finding duration: = "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

        for (const auto &txtFile: txtFiles)
            txtFile->printOccurrences();


        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

/*
 * Handles user input arguments
 */
void handleUserInput(const int argc, char *argv[]) {
    if (argc < 3)
        throw std::runtime_error(
                "less than 3 arguments provided. Usage: ./string_finder <path|file.txt> <string_to_find>");
    if (argc > 3)
        throw std::runtime_error(
                "more than 3 arguments provided. Usage: ./string_finder <path|file.txt> <string_to_find>");
    if (std::string(argv[2]).length() > 128) throw std::runtime_error("string to find is longer than 128 characters.");
}

void searchInFile(std::unique_ptr<File> &file, const std::shared_ptr<BadMatchTable> &badMatchTable,
                  const std::string &needle) {
    file->findOccurrences(badMatchTable, needle);
}

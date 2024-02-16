#include <vector>
#include <iostream>

#include "include/Occurrence.h"


void handleUserInput(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    try {
        handleUserInput(argc, argv);

        std::string toFind(argv[2]);
        fs::path rootPath((std::string(argv[1])));
        std::vector<fs::path> txtFiles;

        findTxtFiles(rootPath, txtFiles);

        BadMatchTable badMatchTable(toFind);

        std::vector<Occurrence> occurrences;

        for (const auto& txtFile : txtFiles)
            findOccurrences(&occurrences, txtFile, badMatchTable, toFind);


        for (const auto& occurrence : occurrences)
            occurrence.print();


        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}

void handleUserInput(int argc, char* argv[]) {
    if (argc < 3) throw std::runtime_error("less than 3 arguments provided.");
    if (argc > 3) throw std::runtime_error("more than 3 arguments provided.");
    if (std::string(argv[2]).length() > 128) throw std::runtime_error("string to find is longer than 128 characters.");
}

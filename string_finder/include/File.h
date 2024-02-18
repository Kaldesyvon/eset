#ifndef STRING_FINDER_FILE_H
#define STRING_FINDER_FILE_H

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <vector>
#include <boost/filesystem.hpp>

#include "BadMatchTable.h"
#include "Occurrence.h"


namespace fs = boost::filesystem;


class File {
public:
    explicit File(const fs::path& path);
    ~File();

    void findOccurrences(const BadMatchTable &badMatchTable, const std::string& needle);
    void print();
    void printOccurrences();
private:
    std::string fileName;
    fs::path path;
    std::vector<std::unique_ptr<Occurrence>> occurrences;

    void createOccurrence(const char *haystack, size_t haystackIndex, uint8_t needleLength);
};
void findTxtFiles(const fs::path& root, std::vector<fs::path>& txtFiles);


#endif //STRING_FINDER_FILE_H

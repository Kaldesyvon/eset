#ifndef STRING_FINDER_FILE_H
#define STRING_FINDER_FILE_H

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include <boost/filesystem.hpp>
#include <vector>

#include "BadMatchTable.h"
#include "Occurrence.h"


namespace fs = boost::filesystem;


class File {
public:
    void findOccurrences(const BadMatchTable &badMatchTable, const std::string& needle);
    void printOccurrences() const;

    ~File();
    explicit File(const fs::path& path);
private:
    fs::path path;
    std::vector<std::unique_ptr<Occurrence>> occurrences;

    void createOccurrence(const char *haystack, size_t haystackIndex, uint8_t needleLength);
};


#endif //STRING_FINDER_FILE_H

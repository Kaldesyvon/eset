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

/*
 * File class so we can find occurrences in file and holds info about file; occurrences and path
 */
class File {
public:
    /*
     * Method that search file's content and find occurrence of needles in haystack and saves them into private vector.
     */
    void findOccurrences(const std::shared_ptr<BadMatchTable> &badMatchTable, const std::string& needle);
    /*
     * Prints all occurrences in file.
     */
    void printOccurrences() const;

    /*
     * Constructor for File class. It takes file's path as an argument.
     */
    explicit File(const fs::path& path);
    ~File();
private:
    fs::path path;
    std::vector<std::unique_ptr<Occurrence>> occurrences;

    /*
     * Internal method for creating occurrence object and storing it in file's member variable of occurrences.
     */
    void createOccurrence(const char *haystack, size_t haystackIndex, uint8_t needleLength);
};


#endif //STRING_FINDER_FILE_H

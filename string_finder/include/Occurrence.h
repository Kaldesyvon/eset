#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include <boost/filesystem.hpp>

#include "BadMatchTable.h"


namespace fs = boost::filesystem;

class Occurrence {
public:
    void print() const;

    void setPrefix(const std::string& haystack, size_t haystackIndex, uint8_t needleLength);
    void setSuffix(const std::string& haystack, size_t haystackIndex);

    Occurrence(size_t at_index, fs::path path);
private:
    const size_t at_index;
    std::string prefix;
    std::string suffix;
    const fs::path path;
};

#endif //STRING_FINDER_OCCURRENCE_H

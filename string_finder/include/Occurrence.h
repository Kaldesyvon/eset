#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <boost/filesystem.hpp>

#include "BadMatchTable.h"

namespace fs = boost::filesystem;

class Occurrence {
public:
    Occurrence(size_t at_index, fs::path path);

    void print() const;

    void setPrefix(const std::string& haystack, size_t haystackIndex, uint8_t needleLength);
    void setSuffix(const std::string& haystack, size_t haystackIndex);
private:
    size_t at_index;
    std::string prefix;
    std::string suffix;
    const fs::path path;
};

#endif //STRING_FINDER_OCCURRENCE_H

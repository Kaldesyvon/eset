#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <unordered_map>
#include <vector>
#include <cstdint>

#include "file.h"
#include "err.h"
#include "BadMatchTable.h"


class Occurrence {
public:
    void print() const;

    Occurrence(size_t at_index, std::string prefix, std::string suffix, std::string file);
private:
};

#endif //STRING_FINDER_OCCURRENCE_H

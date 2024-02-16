#ifndef STRING_FINDER_BADMATCHTABLE_H
#define STRING_FINDER_BADMATCHTABLE_H

#include <unordered_map>
#include <string>
#include <memory>

class BadMatchTable {
private:
    std::unique_ptr<std::unordered_map<char, int>> table;
    void insertPair(uint8_t needleLength, uint8_t needleIndex, char characterToFind);

public:
    explicit BadMatchTable(const std::string& needle);
    size_t getShiftValue(char character) const;
};

#endif //STRING_FINDER_BADMATCHTABLE_H

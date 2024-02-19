#ifndef STRING_FINDER_BADMATCHTABLE_H
#define STRING_FINDER_BADMATCHTABLE_H

#include <memory>
#include <string>
#include <unordered_map>


class BadMatchTable {
public:
    size_t getShiftValue(char character) const;

    explicit BadMatchTable(const std::string& needle);
private:
    std::unique_ptr<std::unordered_map<char, int>> table;

    void insertPair(uint8_t needleLength, uint8_t needleIndex, char characterToFind);
};

#endif //STRING_FINDER_BADMATCHTABLE_H

#include <algorithm>

#include "../include/BadMatchTable.h"


/*
 * Creates bad match table and as for last character adds pair * and length of needle. More details on insertPair() function
 */
BadMatchTable::BadMatchTable(const std::string& needle) : table(std::make_unique<std::unordered_map<char, int>>()) {
    uint8_t needleLength = needle.length();

    for (uint8_t needleIndex = 0; needleIndex < needleLength; needleIndex++) {
        char characterToFind = needle[needleIndex];
        insertPair(needleLength, needleIndex, characterToFind);
    }
    table->insert({'*', needleLength});
}

/*
 * Based on created bad match table method returns shift value for corresponding character in bad match table.
 * If character is not in bad match table then shift value with '*' is returned.
 */
size_t BadMatchTable::getShiftValue(const char character) const {
    const auto found = table->find(character);
    if (found != table->end()) {
        return found->second;
    }
    return table->at('*');
}

/*
 * Inserts a pair of a character and its value calculated from max(1, needle_length + index_of_character_in_needle - 1).
 * When character already exists in bad match table the value is updated.
 */
void BadMatchTable::insertPair(const uint8_t needleLength, const uint8_t needleIndex, const char characterToFind) {
    bool isLastChar = (needleIndex == needleLength - 1);
    auto occurrence = table->find(characterToFind);

    if (!isLastChar || (occurrence == table->end())) {
        int shiftValue = isLastChar ? static_cast<int>(needleLength) : std::max(1, static_cast<int>(needleLength - needleIndex - 1));
        (*table)[characterToFind] = shiftValue;
    }
}

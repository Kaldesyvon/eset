#include "../include/BadMatchTable.h"

#include <algorithm>

BadMatchTable::BadMatchTable(const std::string& needle) : table(std::make_unique<std::unordered_map<char, int>>()) {
    uint8_t needleLength = needle.length();

    for (uint8_t needleIndex = 0; needleIndex < needleLength; needleIndex++) {
        char characterToFind = needle[needleIndex];
        insertPair(needleLength, needleIndex, characterToFind);
    }
    table->insert({'*', needleLength});
}

size_t BadMatchTable::getShiftValue(char character) const {
    auto found = table->find(character);
    if (found != table->end()) {
        return found->second;
    }
    return table->at('*');
}

void BadMatchTable::insertPair(uint8_t needleLength, uint8_t needleIndex, char characterToFind) {
    bool isLastChar = (needleIndex == needleLength - 1);
    auto occurrence = table->find(characterToFind);

    if (!isLastChar || (occurrence == table->end())) {
        int shiftValue = isLastChar ? static_cast<int>(needleLength) : std::max(1, static_cast<int>(needleLength - needleIndex - 1));
        (*table)[characterToFind] = shiftValue;
    }
}
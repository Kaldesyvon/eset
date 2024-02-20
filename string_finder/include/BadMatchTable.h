#ifndef STRING_FINDER_BADMATCHTABLE_H
#define STRING_FINDER_BADMATCHTABLE_H

#include <memory>
#include <string>
#include <unordered_map>

/*
 * In Boyer-Moore algorithm there is bad match table which tells how to move index in haystack in looking for needle,
 * so string search is more effective with fewer comparisons made than in bruteforce search.
 * More on: https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
 */
class BadMatchTable {
public:
    /*
     * Returns a value of what index should move further
     */
    size_t getShiftValue(char character) const;

    /*
     * Constructor of bad match table. It takes string to find as an argument
     */
    explicit BadMatchTable(const std::string& needle);
private:
    std::unique_ptr<std::unordered_map<char, int>> table;

    /*
     * Internal function that wraps functionality of adding a pair of character and jump value into bad match table
     */
    void insertPair(uint8_t needleLength, uint8_t needleIndex, char characterToFind);
};

#endif //STRING_FINDER_BADMATCHTABLE_H

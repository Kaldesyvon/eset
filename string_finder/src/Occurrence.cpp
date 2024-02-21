#include <iostream>
#include <string>
#include <utility>

#include "../include/Occurrence.h"


/*
 * Constructor for Occurrence. It takes index as argument
 */
Occurrence::Occurrence(size_t position)
        : atIndex(position)
{

}

/*
 * Prints an occurrence's info in desired format.
 */
void Occurrence::print() const {
    std::cout << "(" << atIndex << "):" << prefix << "..." << suffix << "\n";
}

/*
 * Internal function that escape \n and \t and print them as a string
 */
static std::string transformEscapeSeq(const char escapeSeq)
{
    if (escapeSeq == '\t') {
        return "\\t";
    }
    else if (escapeSeq == '\n') {
        return "\\n";
    }
    return std::string(1, escapeSeq); // NOLINT(*-return-braced-init-list)
}

/*
 * Setter for setting prefix.
 * It looks into maximum of 3 chars before needle, escape sequences and concatenates chars into prefix
 */
void Occurrence::setPrefix(const std::string& haystack, const size_t haystackIndex, const uint8_t needleLength)
{
    const size_t needleStartIndex = haystackIndex- (needleLength - 1);

    const uint8_t prefixLength = (uint8_t)std::min(static_cast<size_t>(3), needleStartIndex);

    const size_t prefixStart = needleStartIndex - prefixLength;

    for (uint8_t prefixInc = 0; prefixInc < prefixLength; prefixInc++) {
        const char prefixChar = haystack[prefixStart + prefixInc];
        prefix += transformEscapeSeq(prefixChar);
    }
}

/*
 * Setter for setting suffix.
 * It looks into maximum of 3 chars after needle, escape sequences and concatenates chars into suffix
 */
void Occurrence::setSuffix(const std::string& haystack, const size_t haystackIndex)
{
    const size_t haystackLength = haystack.length();

    const uint8_t suffixLength = (uint8_t)std::min(static_cast<size_t>(3), haystackLength - haystackIndex);

    for (size_t suffixInc = haystackIndex + 1; suffixInc <= haystackIndex + suffixLength; suffixInc++) {
        const char suffixChar = haystack[suffixInc];

        suffix += transformEscapeSeq(suffixChar);
    }
}

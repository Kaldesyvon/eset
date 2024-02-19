#include <iostream>
#include <string>
#include <utility>

#include "../include/Occurrence.h"


void Occurrence::print() const {
    std::cout << path.string() << "(" << at_index << "):" << prefix << "..." << suffix << "\n";
}

Occurrence::Occurrence(size_t at_index, fs::path path)
        : at_index(at_index), path(std::move(path))
{

}

std::string transformEscapeSeq(const char escapeSeq)
{
    if (escapeSeq == '\t') {
        return "\\t";
    }
    else if (escapeSeq == '\n') {
        return "\\n";
    }
    return std::string(1, escapeSeq); // NOLINT(*-return-braced-init-list)
}

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

void Occurrence::setSuffix(const std::string& haystack, const size_t haystackIndex)
{
    const size_t haystackLength = haystack.length();

    const uint8_t suffixLength = (uint8_t)std::min(static_cast<size_t>(3), haystackLength - haystackIndex);

    for (size_t suffixInc = haystackIndex + 1; suffixInc <= haystackIndex + suffixLength; suffixInc++) {
        const char suffixChar = haystack[suffixInc];

        suffix += transformEscapeSeq(suffixChar);
    }
}

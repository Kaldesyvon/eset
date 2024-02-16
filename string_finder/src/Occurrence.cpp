#include <iostream>
#include <string>


#include "../include/Occurrence.h"
#include "../include/MappedMemory.h"


void findOccurrences(std::vector<Occurrence>* occurrences, const fs::path& path, const BadMatchTable &badMatchTable,
                     const std::string& needle)
{
    // tu bude files vector a z neho si tato funckia bude brat fily.
    MappedFile mappedMemory(path.c_str());

    auto haystack = mappedMemory.getData();
    auto haystackLength = mappedMemory.getLength();

    uint8_t needleLength = needle.length();

    uint8_t needleLastCharIndex = needleLength - 1;

    size_t haystackIndex = needleLastCharIndex;

    while (haystackIndex < haystackLength) {
        int needleIndex = needleLastCharIndex;
        size_t matchIndex = haystackIndex - needleLastCharIndex;

        while (needleIndex >= 0 && needle[needleIndex] == haystack[matchIndex + needleIndex]) {
            needleIndex--;
        }
        if (needleIndex < 0) {
            Occurrence occurrence = createOccurrence(haystack, haystackIndex, needle, path);
            occurrences->push_back(occurrence);
            haystackIndex += needleLength;
        }
        else {
            uint8_t shift = badMatchTable.getShiftValue(haystack[haystackIndex]);
            haystackIndex += shift;
        }
    }

    munmap(haystack, haystackLength);
}



Occurrence::Occurrence(size_t at_index, std::string prefix, std::string suffix, std::string file)
        : at_index(at_index), prefix(std::move(prefix)), suffix(std::move(suffix)), file(std::move(file)) {

}

void Occurrence::print() const {
    std::cout << file << "(" << at_index << "):" << prefix << "..." << suffix << "\n";
}

std::string transformEscapeSeq(char escapeSeq)
{
    if (escapeSeq == '\t') {
        return "\\t";
    }
    else if (escapeSeq == '\n') {
        return "\\n";
    }
    return std::string(1, escapeSeq); // NOLINT(*-return-braced-init-list)
}


std::string createPrefix(const std::string& haystack, size_t needleEndIndex, uint8_t needleLength)
{
    std::string prefix;

    size_t needleStartIndex = needleEndIndex - (needleLength - 1);

    uint8_t prefixLength = (uint8_t)std::min(static_cast<size_t>(3), needleStartIndex);

    size_t prefixStart = needleStartIndex - prefixLength;

    for (uint8_t prefixInc = 0; prefixInc < prefixLength; prefixInc++) {
        char prefixChar = haystack[prefixStart + prefixInc];
        prefix += transformEscapeSeq(prefixChar);
    }

    return prefix;
}

std::string createSuffix(const std::string& haystack, size_t needleEndIndex)
{
    std::string suffix;

    size_t haystackLength = haystack.length();

    uint8_t suffixLength = (uint8_t)std::min(static_cast<size_t>(3), haystackLength - needleEndIndex);

    for (size_t suffixInc = needleEndIndex + 1; suffixInc <= needleEndIndex + suffixLength; suffixInc++) {
        char suffixChar = haystack[suffixInc];

        suffix += transformEscapeSeq(suffixChar);
    }

    return suffix;
}


#include "../include/File.h"
#include "../include/MappedMemory.h"


File::File(const fs::path& path) {
    this->path = path;
}

File::~File()= default;

void File::findOccurrences(const BadMatchTable &badMatchTable, const std::string &needle) {
    // tu bude files vector a z neho si tato funckia bude brat fily.
    const MappedFile mappedMemory(path.c_str());

    const auto haystack = mappedMemory.getData();
    const auto haystackLength = mappedMemory.getLength();

    const uint8_t needleLength = needle.length();

    const uint8_t needleLastCharIndex = needleLength - 1;

    size_t haystackIndex = needleLastCharIndex;

    while (haystackIndex < haystackLength) {
        int needleIndex = needleLastCharIndex;
        const size_t matchIndex = haystackIndex - needleLastCharIndex;

        while (needleIndex >= 0 && needle[needleIndex] == haystack[matchIndex + needleIndex]) {
            needleIndex--;
        }
        if (needleIndex < 0) {
            createOccurrence(haystack, haystackIndex, needleLength);
            haystackIndex += needleLength;
        }
        else {
            const uint8_t shift = badMatchTable.getShiftValue(haystack[haystackIndex]);
            haystackIndex += shift;
        }
    }
}

void File::createOccurrence(const char *haystack, const size_t haystackIndex, const uint8_t needleLength) {
    auto occurrence = std::make_unique<Occurrence>(haystackIndex + 1 - needleLength, path);
    occurrence->setPrefix(haystack, haystackIndex, needleLength);
    occurrence->setSuffix(haystack, haystackIndex);
    occurrences.push_back(std::move(occurrence));
}

void File::printOccurrences() const {
    for (const auto& occurrence : occurrences)
        occurrence->print();
}




#include "../include/File.h"
#include "../include/MappedMemory.h"


File::File(const fs::path& path) {
    this->path = path;
    this->fileName = path.filename().string();
}

File::~File()= default;

void File::findOccurrences(const BadMatchTable &badMatchTable, const std::string &needle) {
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
            createOccurrence(haystack, haystackIndex, needleLength);
            haystackIndex += needleLength;
        }
        else {
            uint8_t shift = badMatchTable.getShiftValue(haystack[haystackIndex]);
            haystackIndex += shift;
        }
    }
}

void File::createOccurrence(const char *haystack, size_t haystackIndex, uint8_t needleLength) {
    auto occurrence = std::make_unique<Occurrence>(haystackIndex + 1 - needleLength, path);
    occurrence->setPrefix(haystack, haystackIndex, needleLength);
    occurrence->setSuffix(haystack, haystackIndex);
    occurrences.push_back(std::move(occurrence));
}

void File::print() {
    std::cout << fileName << std::endl;

}

void File::printOccurrences() {
    for (const auto& occurrence : occurrences)
        occurrence->print();
}




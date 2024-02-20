#include "../include/File.h"
#include "../include/MappedMemory.h"


/*
 * This object contains information about specific file.
 * Every File object contains its occurrences in it.
 * With this approach there is no need for creating mutexes to write into occurrence vector; every File fills its own
 * vector with no race condition.
 */
File::File(const fs::path& path) {
    this->path = path;
}

File::~File() = default;

/*
 * Most important method. Here is actual Boyer-Moore algorithm located.
 * First step is mapping file's content into MappedFile class
 * Indexing of haystack starts from 0.
 * Last character of needle is compared with haystack at some index.
 * When characters don't match, based on bad match table (in BMT is looking for needle's last character is compared to)
 * haystack index is being increased thus reducing number of steps.
 * Otherwise, second character from end is being compared. When mismatch happen previous step is applied.
 * When all characters in needle are matching method call it occurrence.
 * Occurrence object would be created and added to vector of occurrences.
 * This repeats until end of file.
 */
void File::findOccurrences(const std::shared_ptr<BadMatchTable> &badMatchTable, const std::string &needle) {
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
            const uint8_t shift = badMatchTable->getShiftValue(haystack[haystackIndex]);
            haystackIndex += shift;
        }
    }
}

/*
 * Creates instance of Occurrence, sets prefix, suffix and position.
 * Then it is added to vector of occurrences.
 */
void File::createOccurrence(const char *haystack, const size_t haystackIndex, const uint8_t needleLength) {
    auto occurrence = std::make_unique<Occurrence>(haystackIndex + 1 - needleLength);
    occurrence->setPrefix(haystack, haystackIndex, needleLength);
    occurrence->setSuffix(haystack, haystackIndex);
    occurrences.push_back(std::move(occurrence));
}

/*
 * Prints occurrences in file.
 */
void File::printOccurrences() const {
    for (const auto& occurrence : occurrences){
        std::cout << path.string();
        occurrence->print();
    }
}




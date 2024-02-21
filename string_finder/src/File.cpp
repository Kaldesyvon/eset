#include "../include/File.h"
#include "../include/MappedFile.h"


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
 * First step is mapping file's haystack into MappedFile class
 * Indexing of haystack starts from 0.
 * Last character of needle is compared with haystack at some index.
 * When characters don't match, based on bad match table (in BMT is looking for needle's last character is compared to)
 * haystack index is being increased thus reducing number of steps.
 * Otherwise, second character from end is being compared. When mismatch happens previous step applies.
 * When all characters in needle are matching method call it occurrence.
 * Occurrence object would be created and added to vector of occurrences.
 * This repeats until end of file.
 */
void File::findOccurrences(const std::shared_ptr<BadMatchTable> &badMatchTable, const std::string &needle) {
    const auto mappedMemory = std::make_unique<MappedFile>(path.c_str());

    const auto haystack = mappedMemory->getData();
    const auto haystackLength = mappedMemory->getLength();

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

/*
 * Find all .txt in input directory, checks if it exists and return vector of files.
 * If input is .txt file it returns vector with one file.
 */
std::vector<std::unique_ptr<File>> File::findTxtFiles(const fs::path& root)
{
    // TODO: maybe try to check right for dirs
    if (!fs::exists(root))
        throw std::runtime_error(root.string() + " does not exists.");

    if (!fs::is_directory(root) && fs::extension(root) != FILE_EXTENSION)
        throw std::runtime_error(root.string() + " is neither .txt file nor directory.");

    std::vector<std::unique_ptr<File>> txtFiles;

    if(fs::extension(root) == ".txt") {
        txtFiles.push_back(std::make_unique<File>(root));
        return txtFiles;
    }

    fs::recursive_directory_iterator iterator(root), end;

    while (iterator != end) {
        if (fs::is_regular_file(*iterator) && iterator->path().extension() == ".txt") {
            txtFiles.push_back(std::make_unique<File>(iterator->path()));
        }
        iterator++;
    }

    if (txtFiles.empty())
        throw std::runtime_error("no .txt files found.");

    return txtFiles;
}

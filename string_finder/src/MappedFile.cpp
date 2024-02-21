#include "../include/MappedFile.h"

/*
 * Class that hold data when file is mapped with mmap().
 * Constructor does error checking and utilizes mmap() function.
 * std::ifstream cannot be used with mmap so classic open() is used.
 */
MappedFile::MappedFile(const char* path) {
    fileDescriptor = open(path, O_RDONLY);

    if (fileDescriptor == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to open " + std::string(path));
    }

    if (fstat(fileDescriptor, &fileInfo) == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to get file stat of " + std::string(path));
    }

    mapped = mmap(nullptr, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);

    if (mapped == MAP_FAILED) {
        throw std::system_error(errno, std::generic_category(), "Failed to map " + std::string(path));
    }
    fileLength = fileInfo.st_size;
}

/*
 * Destructor for properly deallocating resources.
 */
MappedFile::~MappedFile() {
    if (mapped != MAP_FAILED) {
        munmap(mapped, fileLength);
    }
    if (fileDescriptor != -1) {
        close(fileDescriptor);
    }
}

/*
 * Getter for file's haystack.
 */
char* MappedFile::getData() const {
    return static_cast<char*>(mapped);
}

/*
 * Getter for file haystack's length.
 */
size_t MappedFile::getLength() const {
    return fileLength;
}

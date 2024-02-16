//
// Created by martin on 2/16/24.
//

#include "../include/MappedMemory.h"


MappedFile::MappedFile(const char* path) {
    fileDescriptor = open(path, O_RDONLY);
    if (fileDescriptor == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to open file");
    }

    if (fstat(fileDescriptor, &fileInfo) == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to get file stat");
    }

    mapped = mmap(nullptr, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);
    if (mapped == MAP_FAILED) {
        throw std::system_error(errno, std::generic_category(), "Failed to map file");
    }
    fileLength = fileInfo.st_size;
}

MappedFile::~MappedFile() {
    if (mapped != MAP_FAILED) {
        munmap(mapped, fileLength);
    }
    if (fileDescriptor != -1) {
        close(fileDescriptor);
    }
}

char* MappedFile::getData() const {
    return static_cast<char*>(mapped);
}

size_t MappedFile::getLength() const {
    return fileLength;
}
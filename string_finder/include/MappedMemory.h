//
// Created by martin on 2/16/24.
//

#ifndef STRING_FINDER_MAPPEDMEMORY_H
#define STRING_FINDER_MAPPEDMEMORY_H

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

class MappedFile {
public:
    explicit MappedFile(const char* path);
    ~MappedFile();

    MappedFile(const MappedFile&) = delete;
    MappedFile& operator=(const MappedFile&) = delete;

    char* getData() const;
    size_t getLength() const;

private:
    int fileDescriptor = -1;
    struct stat fileInfo{};
    void* mapped = MAP_FAILED;
    size_t fileLength = 0;
};


#endif //STRING_FINDER_MAPPEDMEMORY_H

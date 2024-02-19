#ifndef STRING_FINDER_MAPPEDMEMORY_H
#define STRING_FINDER_MAPPEDMEMORY_H

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>


class MappedFile {
public:
    char* getData() const;
    size_t getLength() const;

    MappedFile(const MappedFile&) = delete;
    MappedFile& operator=(const MappedFile&) = delete;

    explicit MappedFile(const char* path);
    ~MappedFile();
private:
    int fileDescriptor = -1;
    struct stat fileInfo{};
    void* mapped = MAP_FAILED;
    size_t fileLength = 0;
};


#endif //STRING_FINDER_MAPPEDMEMORY_H

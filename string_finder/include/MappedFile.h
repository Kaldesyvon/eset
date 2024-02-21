#ifndef STRING_FINDER_MAPPEDFILE_H
#define STRING_FINDER_MAPPEDFILE_H

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * This class holds information about mapped file's contend as for we used mmap() to process large files relatively fast.
 */
class MappedFile {
public:
    /*
     * Getter for file's haystack aka haystack.
     */
    char* getData() const;
    /*
     * Getter for file's haystack length.
     */
    size_t getLength() const;

    /*
     * This two lines secures that MappedFile pointer cannot be copied.
     */
    MappedFile(const MappedFile&) = delete;
    MappedFile& operator=(const MappedFile&) = delete;

    /*
     * Constructor for MappedFile.
     */
    explicit MappedFile(const char* path);
    ~MappedFile();
private:
    /*
     * Member variables for storing data.
     */
    int fileDescriptor = -1;
    struct stat fileInfo{};
    void* mapped = MAP_FAILED;
    size_t fileLength = 0;
};


#endif //STRING_FINDER_MAPPEDFILE_H

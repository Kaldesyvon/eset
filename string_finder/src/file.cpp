#include "../include/file.h"


void find_txt_files(const fs::path& root, std::vector<fs::path>& txt_files)
{
    // TODO: maybe try to check right for dirs
    if (!fs::exists(root))
        throw std::runtime_error(root.string() + " does not exists.");

    if (!fs::is_directory(root) && fs::extension(root) != ".txt")
        throw std::runtime_error(root.string() + " is neither .txt file nor directory.");

    if(fs::extension(root) == ".txt") {
        txt_files.push_back(root);
        return;
    }

    fs::recursive_directory_iterator iterator(root), end;

    while (iterator != end) {
        if (fs::is_regular_file(*iterator) && iterator->path().extension() == ".txt") {
            txt_files.push_back(iterator->path());
        }
        iterator++;
    }
}

std::pair<char*, size_t> get_file_content(const char *path)
{
    int fd = open(path, O_RDWR);
    if (fd == -1) {
        throw std::runtime_error(std::string(path) + " did not opened correctly. Try to check rights.");
    }
    try {
        struct stat file_info{};
        if (stat(path, &file_info) == -1) {
            throw std::runtime_error("getting size of " + std::string(path) + " did not worked correctly. Try to check rights.");
        }

        size_t file_size = file_info.st_size;

        void* mapped_mem = mmap(nullptr, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (mapped_mem == MAP_FAILED) {
            munmap(mapped_mem, file_size);
            throw std::runtime_error("mapping of " + std::string(path) + " was not done correctly. Try to check rights.");
        }

        close(fd);
        return {static_cast<char*>(mapped_mem), file_size};
    } catch (...) {
        close(fd);
        throw;
    }
}
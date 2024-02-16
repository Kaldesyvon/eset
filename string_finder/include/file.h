#ifndef STRING_FINDER_FILE_H
#define STRING_FINDER_FILE_H

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <vector>
#include <boost/filesystem.hpp>

#include "err.h"


namespace fs = boost::filesystem;

std::pair<char*, size_t> get_file_content(const char *path);
void find_txt_files(const fs::path& root, std::vector<fs::path>& txt_files);


#endif //STRING_FINDER_FILE_H

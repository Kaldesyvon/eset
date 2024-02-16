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

void findTxtFiles(const fs::path& root, std::vector<fs::path>& txtFiles);


#endif //STRING_FINDER_FILE_H

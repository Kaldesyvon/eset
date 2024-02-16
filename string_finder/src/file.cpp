#include "../include/file.h"


void findTxtFiles(const fs::path& root, std::vector<fs::path>& txtFiles)
{
    // TODO: maybe try to check right for dirs
    if (!fs::exists(root))
        throw std::runtime_error(root.string() + " does not exists.");

    if (!fs::is_directory(root) && fs::extension(root) != ".txt")
        throw std::runtime_error(root.string() + " is neither .txt file nor directory.");

    if(fs::extension(root) == ".txt") {
        txtFiles.push_back(root);
        return;
    }

    fs::recursive_directory_iterator iterator(root), end;

    while (iterator != end) {
        if (fs::is_regular_file(*iterator) && iterator->path().extension() == ".txt") {
            txtFiles.push_back(iterator->path());
        }
        iterator++;
    }
}


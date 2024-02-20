#ifndef STRING_FINDER_OCCURRENCE_H
#define STRING_FINDER_OCCURRENCE_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include <boost/filesystem.hpp>


namespace fs = boost::filesystem;


/*
 * Class that holds info about occurrence in file when needle is found in haystack.
 * It holds information such as prefix suffix and position.
 */
class Occurrence {
public:
    /*
     * Prints occurrence in desired format.
     */
    void print() const;

    /*
     * Setters for prefix and suffix. It hides implementation of more complex logic.
     */
    void setPrefix(const std::string& haystack, size_t haystackIndex, uint8_t needleLength);
    void setSuffix(const std::string& haystack, size_t haystackIndex);

    /*
     * Constructor for occurrence that takes position of occurrence and path of file.
     * TODO: maybe we dont need path to store it in occurrence
     */
    explicit Occurrence(size_t at_index);
private:
    const size_t at_index;
    std::string prefix;
    std::string suffix;
};

#endif //STRING_FINDER_OCCURRENCE_H

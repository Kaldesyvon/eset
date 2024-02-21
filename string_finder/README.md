# string_finder

This program finds strings and its prefix and suffix in .txt files.
Program uses Boyer-Moore algorithm to find it effectively.
Program also utilizes multithreading, where for each file thread is created.
For understanding: haystack means file's haystack and needle means string to find. As we were finding needle in haystack :)
Program was developed by Martin Novysedlak in 2.2024 in Clion on Pop_OS! operating system for Eset challenge: https://join.eset.com/en/challenges/c-developer

# Prerequisites
* boost >= 1.74
* c++ >= c++14.
* 
# Usage
* build with cmake
* to run program `./string_finder <path | file.txt> <string to find>`

# Performance
Performance depends on what string is to be found. When fore example letter *m* is to be found the performance rapidly drops and program take very long time to run.
Still we can compare same word with multithreading and single-threaded solution.

With 5 text files with around 1.6 million characters each the multithreading solution found occurrences within 4s


# Limitations:
Multithreading approach is done by creating thread for every .txt file there is. When only one .txt file is located,
program is as fast as single threaded solution. However, this approach does not require mutexes and shared memory.

Unit tests are missing because I had problems to set up them (linker errors and finding files) but this was not in requirements (but I tried)

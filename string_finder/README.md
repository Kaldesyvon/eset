# string_finder

This program finds strings and its prefix and suffix in .txt files.
Program uses Boyer-Moore algorithm to find it effectively.
Program also utilizes multithreading, where for each file thread is created.
For understanding: haystack means file's content and needle means string to find. As we were finding needle in
haystack :)
Program was developed by Martin Novysedlák in 2.2024 in Clion on Pop_OS! operating system for Eset
challenge: https://join.eset.com/en/challenges/c-developer

# Prerequisites

* boost >= 1.74
* c++ >= c++14.
*

# Usage

* build with cmake
* to run program `./string_finder <path | file.txt> <string to find>`

# Performance

Performance depends on what string is to be found. When for example letter *m* is to be found the performance rapidly
drops and program takes very long time to run.
Still, we can compare same word with multithreading and single-threaded solution.

We searched for word "still" in same files with more than 1.6 million characters where word "still" is 475 times in one
file.

|        | 1     | 5     | 8     | 10    | 20    |
|--------|-------|-------|-------|-------|-------|
| single | 0.31s | 1.5s  | 1.38s | 1.76s | 3.04s |
| multi  | 0.31s | 0.32s | 3.01s | 3.05s | 5.97s |

The columns are number of files in directory. Before every run `sync` command was ran to flush cache.
As we can notice the solution is effective on small amount of files and not so effective on big number of files. The
reason could be because of hardware limits. Tests were performed on AMD Ryzen 5 2500U which supports 8 threads.
As more than 8 files (more than 8 threads are created based on our solution), threads must block each other, thus
reducing performance.
In reality, there are some system processes running so threshold of 8 files (8 threads) is not point of worsening of
multithreading performance.

# Limitations:

Multithreading approach is done by creating thread for every .txt file there is. When only one .txt file is located,
program is as fast as single threaded solution. However, this approach does not require mutexes and shared memory.

Unit tests are missing because I had problems to set up them (linker errors and finding files) but this was not in
requirements (but I tried).

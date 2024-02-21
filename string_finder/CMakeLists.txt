cmake_minimum_required(VERSION 3.26)
project(string_finder)

# Uncomment if you have Boost installed in a non-standard location
#set(Boost_ROOT "C:/MinGW")
#set(Boost_INCLUDE_DIR "C:/MinGW/include")
#set(Boost_LIBRARY_DIR "C:/MinGW/lib")

find_package(Boost 1.74 COMPONENTS system filesystem unit_test_framework REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif ()

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_executable(string_finder main.cpp
        include/Occurrence.h
        include/File.h
        include/MappedFile.h
        include/BadMatchTable.h
        src/Occurrence.cpp
        src/File.cpp
        src/MappedFile.cpp
        src/BadMatchTable.cpp)

target_link_libraries(string_finder PRIVATE ${Boost_LIBRARIES})
target_include_directories(string_finder PRIVATE ${Boost_INCLUDE_DIRS})

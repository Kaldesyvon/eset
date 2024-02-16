cmake_minimum_required(VERSION 3.26)
project(string_finder)

#set(Boost_ROOT "C:/MinGW")
#set(Boost_INCLUDE_DIR "C:/MinGW/include")
#set(Boost_LIBRARY_DIR "C:/MinGW/lib")

find_package(Boost 1.74 COMPONENTS system filesystem REQUIRED)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif ()

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_executable(string_finder main.cpp src/Occurrence.cpp
        include/file.h
        src/file.cpp
        src/MappedMemory.cpp
        include/MappedMemory.h
        src/BadMatchTable.cpp
        include/BadMatchTable.h)

target_link_libraries(string_finder PRIVATE ${Boost_LIBRARIES})

target_include_directories(string_finder PRIVATE ${Boost_INCLUDE_DIRS})

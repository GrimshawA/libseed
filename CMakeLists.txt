project (Conjuring)
cmake_minimum_required(VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

file(GLOB_RECURSE source_files
    "src/*.h*"
    "src/*.cpp"
    "include/*.h*"
)

add_library(conjuring STATIC ${source_files})

include_directories(include
    src)

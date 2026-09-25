cmake_minimum_required(VERSION 3.12...3.31)

project(libdash LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LIBDASH_BUILD_TESTS        "Build the MPD parser tests"                        ON)
option(LIBDASH_BUILD_NETWORK_TEST "Build libdash_networkpart_test (needs a test server)" ON)
set(LIBDASH_SCHEMA_EXAMPLES_DIR "" CACHE PATH
    "Directory with example MPDs (e.g. a MPEGGroup/DASHSchema checkout) to smoke-test the parser against")

# macOS: prefer the SDK / Homebrew libraries over stale frameworks in /Library/Frameworks
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
endif()

# Windows: use the prebuilt dependencies shipped in this repository
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/libxml2
        ${CMAKE_CURRENT_SOURCE_DIR}/libcurl
        ${CMAKE_CURRENT_SOURCE_DIR}/zlib
        ${CMAKE_CURRENT_SOURCE_DIR}/iconv)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(libdash)

if(LIBDASH_BUILD_NETWORK_TEST)
    add_subdirectory(libdash_networkpart_test)
endif()

if(LIBDASH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(libdash_mpd_test)
endif()

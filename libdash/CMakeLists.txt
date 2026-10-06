cmake_minimum_required(VERSION 3.13...3.31)

project(libdash LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LIBDASH_BUILD_TESTS        "Build the MPD parser tests"                        ON)
option(LIBDASH_BUILD_NETWORK_TEST "Build libdash_networkpart_test (its test server is no longer available)" OFF)
set(LIBDASH_SCHEMA_EXAMPLES_DIR "" CACHE PATH
    "Directory with example MPDs (e.g. a MPEGGroup/DASHSchema checkout) to smoke-test the parser against")
set(LIBDASH_EXTRA_MPD_DIR "" CACHE PATH
    "Directory with further MPDs (e.g. downloaded from player sample lists) to run the deep smoke test on")

# macOS: prefer the SDK / Homebrew libraries over stale frameworks in /Library/Frameworks
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
endif()

# Windows: the prebuilt libxml2, libcurl, zlib and iconv shipped in this repository are 32-bit (x86) only.
# They are used for 32-bit builds (e.g. -A Win32). 64-bit builds need the dependencies from elsewhere,
# e.g. vcpkg with the vcpkg.json manifest in this directory (see CMakePresets.json).
set(LIBDASH_BUNDLED_DEPENDENCIES OFF)
if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(LIBDASH_BUNDLED_DEPENDENCIES ON)
    foreach(dependency libxml2 libcurl zlib iconv)
        list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${dependency})
        file(GLOB dlls ${CMAKE_CURRENT_SOURCE_DIR}/${dependency}/bin/*.dll)
        list(APPEND LIBDASH_BUNDLED_DLLS ${dlls})
    endforeach()
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

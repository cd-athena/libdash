find_package(LibXml2)
find_package(ZLIB)
find_package(CURL)
find_package(Threads REQUIRED)

if(NOT LibXml2_FOUND OR NOT ZLIB_FOUND OR NOT CURL_FOUND)
    if(WIN32 AND NOT LIBDASH_BUNDLED_DEPENDENCIES)
        message(FATAL_ERROR
            "libxml2, libcurl or zlib not found. The libraries shipped in this repository are 32-bit only; "
            "for a 64-bit build install them with vcpkg (vcpkg.json) and use the vcpkg toolchain, "
            "e.g. with the 'windows-x64' preset, or configure a 32-bit build with -A Win32.")
    endif()
    message(FATAL_ERROR "libxml2, libcurl and zlib (including development files) are required.")
endif()

file(GLOB_RECURSE libdash_source CONFIGURE_DEPENDS source/*.cpp)

add_library(dash SHARED ${libdash_source})
target_include_directories(dash PUBLIC include)
target_link_libraries(dash PRIVATE LibXml2::LibXml2 CURL::libcurl ZLIB::ZLIB Threads::Threads)

# Copy the bundled 32-bit DLLs next to the library, so that the test programs find them at runtime
if(LIBDASH_BUNDLED_DEPENDENCIES)
    add_custom_command(TARGET dash POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBDASH_BUNDLED_DLLS} $<TARGET_FILE_DIR:dash>)
endif()

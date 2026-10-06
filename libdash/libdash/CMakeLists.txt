find_package(LibXml2)
find_package(ZLIB)
find_package(CURL)
find_package(Threads REQUIRED)

if(NOT LibXml2_FOUND OR NOT ZLIB_FOUND OR NOT CURL_FOUND)
    if(WIN32 AND NOT LIBDASH_BUNDLED_DEPENDENCIES)
        message(FATAL_ERROR
            "libxml2, libcurl or zlib not found. Install them with vcpkg (vcpkg.json) and use the vcpkg toolchain, "
            "e.g. with the 'windows-x64' or 'windows-x86' preset.")
    endif()
    message(FATAL_ERROR "libxml2, libcurl and zlib (including development files) are required.")
endif()

file(GLOB_RECURSE libdash_source CONFIGURE_DEPENDS source/*.cpp)

add_library(dash SHARED ${libdash_source})
target_include_directories(dash PUBLIC include)
target_link_libraries(dash PRIVATE LibXml2::LibXml2 CURL::libcurl ZLIB::ZLIB Threads::Threads)

# The bundled libxml2 is built with iconv support, so its headers include iconv.h.
# Copy the bundled 32-bit DLLs next to the library, so that the test programs find them at runtime.
if(LIBDASH_BUNDLED_DEPENDENCIES)
    target_include_directories(dash PRIVATE ${PROJECT_SOURCE_DIR}/iconv/include)
    add_custom_command(TARGET dash POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBDASH_BUNDLED_DLLS} $<TARGET_FILE_DIR:dash>)
endif()

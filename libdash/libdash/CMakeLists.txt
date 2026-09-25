find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE libdash_source CONFIGURE_DEPENDS source/*.cpp)

add_library(dash SHARED ${libdash_source})
target_include_directories(dash PUBLIC include)
target_link_libraries(dash PRIVATE LibXml2::LibXml2 CURL::libcurl ZLIB::ZLIB Threads::Threads)

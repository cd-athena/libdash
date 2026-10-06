file(GLOB_RECURSE networkpart_source CONFIGURE_DEPENDS *.cpp)

add_executable(libdash_networkpart_test ${networkpart_source})
target_link_libraries(libdash_networkpart_test dash)
if(WIN32)
    target_link_libraries(libdash_networkpart_test ws2_32)
endif()

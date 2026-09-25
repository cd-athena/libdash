add_executable(libdash_mpd_test libdash_mpd_test.cpp)
target_link_libraries(libdash_mpd_test dash)

add_test(NAME mpd_pre6ed_fields
         COMMAND libdash_mpd_test fields ${CMAKE_CURRENT_SOURCE_DIR}/data/pre6ed_fields.mpd)

if(LIBDASH_SCHEMA_EXAMPLES_DIR)
    file(GLOB schema_examples ${LIBDASH_SCHEMA_EXAMPLES_DIR}/*.mpd)
    if(NOT schema_examples)
        message(FATAL_ERROR "No *.mpd files found in LIBDASH_SCHEMA_EXAMPLES_DIR=${LIBDASH_SCHEMA_EXAMPLES_DIR}")
    endif()
    add_test(NAME mpd_schema_examples COMMAND libdash_mpd_test smoke ${schema_examples})
endif()

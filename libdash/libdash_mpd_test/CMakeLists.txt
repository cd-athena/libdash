add_executable(libdash_mpd_test libdash_mpd_test.cpp)
target_link_libraries(libdash_mpd_test dash)

add_test(NAME mpd_pre6ed_fields
         COMMAND libdash_mpd_test fields ${CMAKE_CURRENT_SOURCE_DIR}/data/pre6ed_fields.mpd)
add_test(NAME mpd_segment_sequences
         COMMAND libdash_mpd_test sequences ${CMAKE_CURRENT_SOURCE_DIR}/data/segment_sequences.mpd)
add_test(NAME mpd_url_parameters
         COMMAND libdash_mpd_test urlparams ${CMAKE_CURRENT_SOURCE_DIR}/data/url_parameters.mpd)
add_test(NAME mpd_content_steering
         COMMAND libdash_mpd_test steering ${CMAKE_CURRENT_SOURCE_DIR}/data/content_steering.mpd)
add_test(NAME mpd_cmcd
         COMMAND libdash_mpd_test cmcd ${CMAKE_CURRENT_SOURCE_DIR}/data/cmcd.mpd)
add_test(NAME mpd_alternative_mpd
         COMMAND libdash_mpd_test altmpd ${CMAKE_CURRENT_SOURCE_DIR}/data/alternative_mpd.mpd)
add_test(NAME mpd_imported_mpd
         COMMAND libdash_mpd_test imported ${CMAKE_CURRENT_SOURCE_DIR}/data/list_mpd.mpd
                                           ${CMAKE_CURRENT_SOURCE_DIR}/data/linked_period_resolved.mpd)

if(LIBDASH_SCHEMA_EXAMPLES_DIR)
    file(GLOB schema_examples ${LIBDASH_SCHEMA_EXAMPLES_DIR}/*.mpd)
    if(NOT schema_examples)
        message(FATAL_ERROR "No *.mpd files found in LIBDASH_SCHEMA_EXAMPLES_DIR=${LIBDASH_SCHEMA_EXAMPLES_DIR}")
    endif()
    add_test(NAME mpd_schema_examples COMMAND libdash_mpd_test smoke ${schema_examples})
endif()


if(TARGET_DEV STREQUAL "LINUX_AMD64")
    file(GLOB test_source_files
        "*.cpp"
    )

    add_executable(unittest EXCLUDE_FROM_ALL ${test_source_files})
    target_link_libraries(unittest mc)

    string(TOLOWER ${TARGET_DEV} DEPLOY_DIR)

    add_custom_command(TARGET unittest
                    POST_BUILD
                    COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/bin/${DEPLOY_DIR} &&
                    ${CMAKE_COMMAND} -E copy $<TARGET_FILE:unittest> ${PROJECT_SOURCE_DIR}/bin/${DEPLOY_DIR}
    )
endif()
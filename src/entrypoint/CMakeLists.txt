
string(TOLOWER ${TARGET_DEV} ENTRYPOINT_DIR)

# Get paths to all files under target entrypoint directory
file(GLOB ENTRYPOINT_PATHS ${ENTRYPOINT_DIR}/*.cpp)

# Add all files as executables, e.g. main.cpp will provide executable
# by the name of main
foreach(entrypoint_path ${ENTRYPOINT_PATHS})
    get_filename_component(entrypoint_file ${entrypoint_path} NAME)
    string(REPLACE ".cpp" "" entrypoint ${entrypoint_file})
    add_executable(${entrypoint} ${ENTRYPOINT_DIR}/${entrypoint_file})
    target_link_libraries(${entrypoint} mc)

    add_custom_command(TARGET ${entrypoint}
        POST_BUILD
        COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/bin/${ENTRYPOINT_DIR} &&
        ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${entrypoint}> ${PROJECT_SOURCE_DIR}/bin/${ENTRYPOINT_DIR}
    )
endforeach()
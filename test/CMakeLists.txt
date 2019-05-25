
file(GLOB test_source_files
    "*.cpp"
)

add_custom_target(test)

add_executable(test_exec ${test_source_files})
target_link_libraries(test_exec montecarlolib)
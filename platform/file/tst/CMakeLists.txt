
set(test_name file_test)

addTest(${test_name} 
    "file_mode_test.cpp"
    "file_test.cpp"
    "file_types_test.cpp"
    "main.cpp"
    "path_test.cpp"
)

TARGET_LINK_LIBRARIES(${test_name} file)
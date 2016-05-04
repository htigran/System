
set(test_name file_test)

addTest(${test_name}
    "main.cpp"
)

TARGET_LINK_LIBRARIES(${test_name} file pthread)
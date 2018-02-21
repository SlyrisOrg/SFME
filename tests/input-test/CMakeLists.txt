set(SOURCES input-test.cpp)
CREATE_UNIT_TEST(input-test SFME: "${SOURCES}")
target_link_libraries(input-test SFME::Input)
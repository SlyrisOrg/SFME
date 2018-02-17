set(SOURCES scripting-test.cpp)
CREATE_UNIT_TEST(scripting-test SFME: "${SOURCES}")
target_link_libraries(scripting-test SFME::Scripting)
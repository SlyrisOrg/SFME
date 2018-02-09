set(SOURCES timer-test.cpp)
CREATE_UNIT_TEST(timer-test SFME: "${SOURCES}")
target_link_libraries(timer-test SFME::Timer)
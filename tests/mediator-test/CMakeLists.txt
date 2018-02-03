set(SOURCES mediator-test.cpp)
CREATE_UNIT_TEST(mediator-test SFME: "${SOURCES}")
target_link_libraries(mediator-test SFME::Mediator)
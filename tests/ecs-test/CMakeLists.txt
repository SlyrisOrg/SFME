set(SOURCES ecs-test.cpp)
CREATE_UNIT_TEST(ecs-test SFME: "${SOURCES}")
target_link_libraries(ecs-test SFME::ECS)
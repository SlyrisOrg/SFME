macro(generate_local_test FILENAME EXENAME)
    set(SOURCES ${FILENAME})
    CREATE_UNIT_TEST(${EXENAME} SFME: "${SOURCES}")
    target_link_libraries(${EXENAME} SFME::ECS)
endmacro()

generate_local_test(ecs-system-test.cpp ecs-system-test)
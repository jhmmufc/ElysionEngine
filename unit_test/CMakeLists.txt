set(UNIT_TESTS
    entity_tests.cpp
    main.cpp)
    
add_executable(unit_tests ${UNIT_TESTS})

target_link_libraries(unit_tests PUBLIC elysion_engine)
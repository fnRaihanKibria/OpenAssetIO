add_executable(openassetio-core-c-test
    main.cpp
    managerAPI/CManagerInterfaceTest.cpp)

target_link_libraries(
    openassetio-core-c-test
    PRIVATE
    Catch2::Catch2
    openassetio-core-c
)

target_include_directories(
    openassetio-core-c-test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/openassetio-core-c/private
)

catch_discover_tests(openassetio-core-c-test)

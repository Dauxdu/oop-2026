project(lab-3 LANGUAGES CXX)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    lib/bank.ixx
    lib/BankAccount.cppm
    lib/BankAccountAlgorithms.cppm
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    inx
    console
    ${PROJECT_NAME}_lib
)

if(GTEST_FOUND)
    add_executable(${PROJECT_NAME}_tests
        tests/testBankAccount.cpp
        tests/testBankAccountAlgorithms.cpp
    )
    target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        ${PROJECT_NAME}_lib
    )

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_tests)
endif()

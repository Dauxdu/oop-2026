project(lab-3 LANGUAGES CXX)

add_library(BankAccount STATIC)
target_sources(BankAccount
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
    BankAccount
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
        BankAccount
    )

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_tests)
endif()

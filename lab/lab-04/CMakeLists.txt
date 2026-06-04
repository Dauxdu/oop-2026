project(lab-4 LANGUAGES CXX)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    lib/BankAccounts.ixx
    lib/BankAccount.cppm
    lib/BankAccountAlgorithms.cppm
    lib/CheckingAccount.cppm
    lib/CreditAccount.cppm
    lib/DepositAccount.cppm
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    inx
    console
    ${PROJECT_NAME}_lib
)

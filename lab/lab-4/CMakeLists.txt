project(lab-4 LANGUAGES CXX)

add_library(BankAccounts STATIC)
target_sources(BankAccounts
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
    BankAccounts
)

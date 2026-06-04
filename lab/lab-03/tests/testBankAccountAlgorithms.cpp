#include <gtest/gtest.h>

import bank;

TEST(BankAccountAlgorithms, ApplyInterest_MultipleAccounts_AllUpdated)
{
    std::vector<BankAccount> accounts;
    accounts.emplace_back("A A A", 1200.0, 12.0);
    accounts.emplace_back("B B B", 600.0, 12.0);

    apply_interest(accounts);

    EXPECT_DOUBLE_EQ(accounts[0].get_balance(), 1212.0);
    EXPECT_DOUBLE_EQ(accounts[1].get_balance(), 606.0);
}

TEST(BankAccountAlgorithms, IndexOfMaxBalance_ReturnsIndexOfLargestBalance)
{
    std::vector<BankAccount> accounts;
    accounts.emplace_back("A A A", 100.0, 5.0);
    accounts.emplace_back("B B B", 300.0, 5.0);
    accounts.emplace_back("C C C", 200.0, 5.0);

    EXPECT_EQ(max_balance_index(accounts), 1);
}

#include <gtest/gtest.h>

import bank;

TEST(BankAccount, ApplyMonthlyInterest_PositiveRate_IncreasesBalance)
{
    BankAccount account("A A A", 1200.0, 12.0);
    account.apply_monthly_interest();

    EXPECT_DOUBLE_EQ(account.get_balance(), 1212.0);
}

TEST(BankAccount, ApplyMonthlyInterest_ZeroRate_DoesNotChangeBalance)
{
    BankAccount account("B B B", 1000.0, 0.0);
    account.apply_monthly_interest();

    EXPECT_DOUBLE_EQ(account.get_balance(), 1000.0);
}

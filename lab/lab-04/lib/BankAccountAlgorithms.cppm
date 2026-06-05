/**
 * @file BankAccountAlgorithms.cppm
 * @brief Алгоритмы работы с коллекцией банковских счетов.
 */
export module BankAccounts:BankAccountAlgorithms;

import std;
import :BankAccount;

/**
 * @brief Начисляет проценты всем счетам в коллекции.
 * @param[in, out] accounts Вектор указателей на счета.
 */
export void apply_interest(std::vector<AccountPtr> &accounts)
{
    for (const auto &account : accounts)
    {
        account->apply_monthly_interest();
    }
}

/**
 * @brief Находит индекс счёта с максимальным балансом.
 * @param[in] accounts Вектор указателей на счета.
 * @return Индекс счёта с максимальным балансом или std::nullopt, если вектор пуст.
 */
export std::optional<std::size_t> max_balance_index(const std::vector<AccountPtr> &accounts)
{
    if (accounts.empty())
    {
        return std::nullopt;
    }

    auto it = std::ranges::max_element(accounts, {}, &BankAccount::get_balance);
    return static_cast<std::size_t>(std::distance(accounts.begin(), it));
}

/**
 * @brief Находит индекс счёта с минимальным балансом.
 * @param[in] accounts Вектор указателей на счета.
 * @return Индекс счёта с минимальным балансом или std::nullopt, если вектор пуст.
 */
export std::optional<std::size_t> min_balance_index(const std::vector<AccountPtr> &accounts)
{
    if (accounts.empty())
    {
        return std::nullopt;
    }

    auto it = std::ranges::min_element(accounts, {}, &BankAccount::get_balance);
    return static_cast<std::size_t>(std::distance(accounts.begin(), it));
}

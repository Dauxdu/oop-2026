/**
 * @file BankAccountAlgorithms.cppm
 * @brief Алгоритмы обработки коллекции банковских счетов.
 */
export module bank:BankAccountAlgorithms;

import std;
import :BankAccount;

/**
 * @brief Начисляет ежемесячные проценты всем счетам в коллекции.
 * @param[in, out] accounts Вектор счетов для обработки.
 */
export void apply_interest(std::vector<BankAccount> &accounts)
{
    std::ranges::for_each(accounts, &BankAccount::apply_monthly_interest);
}

/**
 * @brief Находит индекс счёта с максимальным балансом.
 * @param accounts Вектор счетов для поиска.
 * @throws std::invalid_argument Если коллекция пуста.
 * @return Индекс элемента с наибольшим балансом.
 */
export int max_balance_index(const std::vector<BankAccount> &accounts)
{
    if (accounts.empty())
    {
        throw std::invalid_argument("Список счетов пуст");
    }

    auto it = std::ranges::max_element(accounts, {}, &BankAccount::get_balance);
    return it - accounts.begin();
}
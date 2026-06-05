/**
 * @file main.cpp
 * @brief Интерактивное приложение для управления банковскими счетами.
 */
import std;
import inx;
import console;
import bank;

/// @brief Выводит меню доступных операций.
void print_menu()
{
    std::println("[1] Добавить счёт");
    std::println("[2] Удалить счёт");
    std::println("[3] Начислить проценты");
    std::println("[4] Найти максимальный баланс");
    std::println("[5] Выход");
    std::print("\nВыберите пункт: ");
}

/**
 * @brief Форматирует и выводит информацию о всех счетах.
 * @param[in] accounts Вектор счетов для отображения.
 */
void print_accounts(const std::vector<BankAccount> &accounts)
{
    std::println("\nТекущие счета:");

    if (!accounts.empty())
    {
        for (const auto &[index, account] : std::views::enumerate(accounts))
        {
            std::println("{}: {}, баланс {:.2f}, ставка {:.2f}%", index, account.get_owner(), account.get_balance(), account.get_interest_rate());
        }

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Вставляет новый счёт по указанному индексу.
 * @param[in, out] accounts Ссылка на вектор счетов.
 * @note Проверяет ФИО через регулярное выражение (формат: 3 слова).
 */
void insert_account(std::vector<BankAccount> &accounts)
{
    const int index = accounts.empty() ? 0 : inx::input_numeric<int>(std::format("Введите индекс вставки (0-{}): ", accounts.size()), 0, accounts.size());
    std::string owner = inx::input_string("Введите ФИО владельца: ", R"(([A-Za-z]|[^\x00-\x7F])+\s+([A-Za-z]|[^\x00-\x7F])+\s+([A-Za-z]|[^\x00-\x7F])+)");
    const double balance = inx::input_numeric<double>("Введите баланс: ");
    const double rate = inx::input_numeric<double>("Введите ставку (%): ", 0.0);

    accounts.insert(accounts.begin() + index, BankAccount(owner, balance, rate));
    std::println("Счёт добавлен");
}

/**
 * @brief Удаляет счёт по указанному индексу.
 * @param[in, out] accounts Ссылка на вектор счетов.
 */
void erase_account(std::vector<BankAccount> &accounts)
{
    if (!accounts.empty())
    {
        int index = inx::input_numeric<int>(std::format("Введите индекс (0-{}): ", accounts.size() - 1), 0, accounts.size() - 1);
        accounts.erase(accounts.begin() + index);
        std::println("Счёт удалён");
    }
}

/**
 * @brief Применяет начисление процентов ко всем счетам.
 * @param[in, out] accounts Ссылка на вектор счетов.
 */
void apply_interest_to_all(std::vector<BankAccount> &accounts)
{
    if (!accounts.empty())
    {
        apply_interest(accounts);
        std::println("Проценты начислены");
    }
}

/**
 * @brief Находит и выводит информацию о счёте с максимальным балансом.
 * @param[in] accounts Вектор счетов для анализа.
 * @note Делегирует проверку на пустоту алгоритму max_balance_index.
 */
void print_max_balance(const std::vector<BankAccount> &accounts)
{
    const std::size_t index = max_balance_index(accounts);
    const auto &account = accounts[index];

    std::println("-----------------------------------");
    std::println("Счёт с максимальным балансом:");
    std::println("Индекс: {}", index);
    std::println("Владелец: {}", account.get_owner());
    std::println("Баланс: {:.2f}", account.get_balance());
    std::println("-----------------------------------");
}

/**
 * @brief Точка входа программы.
 * @details Запускает цикл меню, делегирует операции модулю bank
 *          и перехватывает исключения, предотвращая аварийное завершение.
 * @return 0 при успешном завершении.
 */
int main()
{
    print_header(3);
    std::println("Привет, {}, это программа управления счетами", get_system_username());

    std::vector<BankAccount> accounts;

    while (true)
    {
        print_accounts(accounts);
        print_menu();

        try
        {
            const int choice = inx::input_numeric<int>(1, 5);
            switch (choice)
            {
            case 1:
                insert_account(accounts);
                break;
            case 2:
                erase_account(accounts);
                break;
            case 3:
                apply_interest_to_all(accounts);
                break;
            case 4:
                print_max_balance(accounts);
                break;
            case 5:
                std::println("До свидания!");
                return 0;
            }
        }
        catch (const std::runtime_error &e)
        {
            std::println("Ошибка: {}", e.what());
            throw;
        }
        catch (const std::exception &e)
        {
            std::println("Ошибка: {}", e.what());
        }
    }

    return 0;
}
/**
 * @file main.cpp
 * @brief Интерактивное приложение для управления банковскими счетами.
 */
import std;
import inx;
import console;
import BankAccounts;

/// @brief Выводит меню доступных операций.
void print_menu()
{
    std::println("-----------------------------------");
    std::println("Меню:");
    std::println("[1] Добавить счёт");
    std::println("[2] Удалить счёт");
    std::println("[3] Показать счета");
    std::println("[4] Начислить проценты");
    std::println("[5] Найти максимальный баланс");
    std::println("[6] Найти минимальный баланс");
    std::println("[7] Показать тип счёта");
    std::println("[8] Выход");
    std::print("\nВыберите пункт: ");
}

/**
 * @brief Выводит список всех счетов.
 * @param[in] accounts Вектор счетов для отображения.
 */
void print_accounts(const std::vector<AccountPtr> &accounts)
{
    std::println("\nТекущие счета:");

    if (!accounts.empty())
    {
        for (const auto &[index, account] : std::views::enumerate(accounts))
        {
            std::print("{}: {} | {} | баланс: {:.2f}", index, account->get_type(), account->get_owner(), account->get_balance());

            if (account->get_interest_rate() > 0.0)
            {
                std::println(" | ставка: {:.2f}%", account->get_interest_rate());
            }
            else
            {
                std::println();
            }
        }

        return;
    }

    std::println("Список пуст.");
}

/**
 * @brief Создаёт новый счёт на основе пользовательского ввода.
 * @return Умный указатель на созданный счёт или nullptr при ошибке.
 */
AccountPtr create_account()
{
    std::println("\nТип счёта:");
    std::println("[1] Расчётный");
    std::println("[2] Вкладовый");
    std::println("[3] Кредитный");

    const int type = inx::input_numeric<int>("\nВыберете тип счёта: ", 1, 3);
    const std::string owner = inx::input_string("Введите ФИО владельца: ", R"(([A-Za-z]|[^\x00-\x7F])+\s+([A-Za-z]|[^\x00-\x7F])+\s+([A-Za-z]|[^\x00-\x7F])+)");
    const double balance = inx::input_numeric<double>("Введите баланс: ");

    try
    {
        if (type == 1)
        {
            return std::make_unique<CheckingAccount>(owner, balance);
        }

        double interest_rate = inx::input_numeric<double>("Введите ставку (%): ");
        if (type == 2)
        {
            return std::make_unique<DepositAccount>(owner, balance, interest_rate);
        }

        return std::make_unique<CreditAccount>(owner, balance, interest_rate);
    }
    catch (const std::exception &e)
    {
        std::println("Ошибка создания счёта: {}", e.what());
        return nullptr;
    }
}

/**
 * @brief Добавляет новый счёт в контейнер.
 * @param[in, out] accounts Вектор счетов для модификации.
 */
void insert_account(std::vector<AccountPtr> &accounts)
{
    const int max_index = accounts.size();
    const int index = accounts.empty() ? 0 : inx::input_numeric<int>(std::format("Введите индекс вставки (0-{}): ", max_index), 0, max_index);

    AccountPtr account = create_account();
    if (account)
    {
        accounts.insert(accounts.begin() + index, std::move(account));
        std::println("Счёт добавлен.\n");
    }
}

/**
 * @brief Удаляет счёт по индексу.
 * @param[in, out] accounts Вектор счетов для модификации.
 */
void erase_account(std::vector<AccountPtr> &accounts)
{
    if (!accounts.empty())
    {
        const int max_index = accounts.size() - 1;
        const int index = inx::input_numeric<int>(std::format("Введите индекс (0-{}): ", max_index), 0, max_index);
        accounts.erase(accounts.begin() + index);
        std::println("Счёт удалён.\n");

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Применяет начисление процентов ко всем счетам.
 * @param[in, out] accounts Вектор счетов.
 */
void apply_interest_to_all(std::vector<AccountPtr> &accounts)
{
    if (!accounts.empty())
    {
        try
        {
            apply_interest(accounts);
            std::println("Проценты начислены.\n");
        }
        catch (const std::exception &e)
        {
            std::println("Ошибка при начислении процентов: {}", e.what());
        }

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Находит и выводит счёт с минимальным балансом.
 * @param[in] accounts Вектор счетов для анализа.
 */
void print_max_balance(const std::vector<AccountPtr> &accounts)
{
    auto index = max_balance_index(accounts);
    if (index)
    {
        const auto &account = accounts[*index];
        std::println("\n-----------------------------------");
        std::println("Счёт с максимальным балансом:");
        std::println("Индекс: {}", *index);
        std::println("Владелец: {}", account->get_owner());
        std::println("Тип: {}", account->get_type());
        std::println("Баланс: {:.2f}", account->get_balance());
        std::println("-----------------------------------\n");

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Находит и выводит счёт с минимальным балансом.
 * @param[in] accounts Вектор счетов для анализа.
 */
void print_min_balance(const std::vector<AccountPtr> &accounts)
{
    auto index = min_balance_index(accounts);
    if (index)
    {
        const auto &account = accounts[*index];
        std::println("\n-----------------------------------");
        std::println("Счёт с минимальным балансом:");
        std::println("Индекс: {}", *index);
        std::println("Владелец: {}", account->get_owner());
        std::println("Тип: {}", account->get_type());
        std::println("Баланс: {:.2f}", account->get_balance());
        std::println("-----------------------------------\n");

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Демонстрирует полиморфное поведение через метод get_type().
 * @param[in] accounts Вектор счетов для демонстрации.
 */
void account_type(const std::vector<AccountPtr> &accounts)
{
    if (!accounts.empty())
    {
        std::println("Типы счётов:");
        for (const auto &[index, account] : std::views::enumerate(accounts))
        {
            std::println("{}: {} -> {}", index, account->get_owner(), account->get_type());
        }

        return;
    }

    std::println("Список пуст.\n");
}

/**
 * @brief Точка входа программы.
 * @return 0 при успешном завершении.
 */
int main()
{
    print_header(4);
    std::println("Привет, {}, это программа управления счетами.", get_system_username());

    std::vector<AccountPtr> accounts;
    while (true)
    {
        try
        {
            print_menu();

            const int choice = inx::input_numeric<int>(1, 8);
            switch (choice)
            {
            case 1:
                insert_account(accounts);
                break;
            case 2:
                erase_account(accounts);
                break;
            case 3:
                print_accounts(accounts);
                break;
            case 4:
                apply_interest_to_all(accounts);
                break;
            case 5:
                print_max_balance(accounts);
                break;
            case 6:
                print_min_balance(accounts);
                break;
            case 7:
                account_type(accounts);
                break;
            case 8:
                std::println("\nДо свидания!");
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
}

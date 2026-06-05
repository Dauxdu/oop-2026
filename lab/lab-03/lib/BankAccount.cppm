/**
 * @file BankAccount.cppm
 * @brief Определение класса BankAccount.
 * @details Реализует логику хранения данных счёта и начисления процентов.
 */
export module bank:BankAccount;

import std;

/**
 * @brief Класс банковского счёта с поддержкой процентной ставки.
 */
export class BankAccount
{
private:
    std::string _owner;
    double _balance{};
    double _interest_rate{};

public:
    /**
     * @brief Конструктор счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Баланс счёта.
     * @param[in] rate Годовая ставка в процентах. Отрицательные значения автоматически заменяются на 0.0.
     */
    BankAccount(std::string owner, double balance, double rate) : _owner(std::move(owner)), _balance(balance), _interest_rate(std::max(0.0, rate))
    {
        if (_owner.empty())
        {
            throw std::invalid_argument("Имя владельца не может быть пустым");
        }
    }

    BankAccount() = delete;

    /// @brief Возвращает ФИО владельца.
    [[nodiscard]] const std::string &get_owner() const { return _owner; }

    /// @brief Возвращает текущий баланс.
    [[nodiscard]] double get_balance() const { return _balance; }

    /// @brief Возвращает годовую процентную ставку (%).
    [[nodiscard]] double get_interest_rate() const { return _interest_rate; }

    /**
     * @brief Начисляет проценты за один месяц.
     * @details Применяется формула: `баланс += баланс * (ставка / 100 / 12)`.
     *          Операция выполняется только при `ставка > 0`.
     */
    void apply_monthly_interest()
    {
        if (_interest_rate > 0.0)
        {
            const double monthly_rate = (_interest_rate / 100.0) / 12.0;
            _balance *= (1.0 + monthly_rate);
        }
    }
};
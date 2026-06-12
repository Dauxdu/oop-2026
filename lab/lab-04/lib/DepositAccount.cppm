/**
 * @file DepositAccount.cppm
 * @brief Реализация вкладового банковского счёта.
 * @details Определяет класс счёта, для которого проценты начисляются на положительный баланс.
 */
export module BankAccounts:DepositAccount;

import std;
import :BankAccount;

/**
 * @brief Вкладовый счёт (проценты на положительный баланс).
 * @details Наследуется от BankAccount. Проценты начисляются только в том случае,
 *          если баланс положительный. Отрицательный баланс процентами не облагается.
 */
export class DepositAccount final : public BankAccount
{
private:
    double _interest_rate{0};

public:
    /**
     * @brief Конструктор вкладового счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     * @param[in] interest_rate Годовая процентная ставка. Отрицательные значения заменяются на 0.0.
     */
    DepositAccount(std::string owner, double balance, double interest_rate) : BankAccount(std::move(owner), balance), _interest_rate(std::max(0.0, interest_rate)) {}

    /// @brief Годовая процентная ставка (%).
    /// @return Годовая ставка в процентах (0.0 по умолчанию).
    double get_interest_rate() const override { return _interest_rate; }

    /**
     * @brief Тип счёта.
     * @return Строковое представление типа счёта ("Вкладовый").
     */
    std::string_view get_type() const override { return "Вкладовый"; }

    /**
     * @brief Начисляет проценты на положительный баланс.
     * @details Если баланс отрицательный или нулевой, операция не выполняется.
     */
    void apply_monthly_interest() override
    {
        if (_interest_rate <= 0.0 || get_balance() <= 0.0)
        {
            return;
        }

        constexpr double PERCENT_TO_DECIMAL = 100.0;
        constexpr double MONTHS_PER_YEAR = 12.0;
        const double monthly_rate = (_interest_rate / PERCENT_TO_DECIMAL) / MONTHS_PER_YEAR;

        set_balance(get_balance() * (1.0 + monthly_rate));
    }
};

/**
 * @file CreditAccount.cppm
 * @brief Реализация кредитного банковского счёта.
 * @details Определяет класс счёта, для которого проценты начисляются на отрицательный баланс (увеличивая долг).
 */
export module BankAccounts:CreditAccount;

import std;
import :BankAccount;

/**
 * @brief Кредитный счёт (проценты на долг).
 * @details Наследуется от BankAccount. Проценты начисляются только в том случае,
 *          если баланс ушёл в минус. Положительный баланс процентами не облагается.
 */
export class CreditAccount final : public BankAccount
{
private:
    double _interest_rate{0};

public:
    /**
     * @brief Конструктор кредитного счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     * @param[in] interest_rate Годовая процентная ставка. Отрицательные значения заменяются на 0.0.
     */
    CreditAccount(std::string owner, double balance, double interest_rate) : BankAccount(std::move(owner), balance), _interest_rate(std::max(0.0, interest_rate)) {}

    /// @brief Годовая процентная ставка (%).
    /// @return Годовая ставка в процентах (0.0 по умолчанию).
    double get_interest_rate() const override { return _interest_rate; }

    /**
     * @brief Тип счёта.
     * @return Строковое представление типа счёта ("Кредитный").
     */
    std::string_view get_type() const override { return "Кредитный"; }

    /**
     * @brief Начисляет проценты на отрицательный баланс (увеличивает долг).
     * @details Если баланс положительный или нулевой, операция не выполняется.
     */
    void apply_monthly_interest() override
    {
        if (_interest_rate <= 0.0 || get_balance() >= 0.0)
        {
            return;
        }

        constexpr double PERCENT_TO_DECIMAL = 100.0;
        constexpr double MONTHS_PER_YEAR = 12.0;
        const double monthly_rate = (_interest_rate / PERCENT_TO_DECIMAL) / MONTHS_PER_YEAR;

        set_balance(get_balance() * (1.0 + monthly_rate));
    }
};

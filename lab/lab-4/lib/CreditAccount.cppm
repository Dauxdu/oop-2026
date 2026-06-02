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
    double _interest_rate{};

    /**
     * @brief Нормализует процентную ставку, гарантируя, что она неотрицательна.
     * @param[in] interest_rate Исходная процентная ставка.
     * @return Неотрицательное значение ставки (минимум 0.0).
     */
    double normalize_rate(double interest_rate) { return std::max(0.0, interest_rate); }

public:
    /**
     * @brief Конструктор кредитного счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     * @param[in] interest_rate Годовая процентная ставка. Отрицательные значения заменяются на 0.0.
     */
    CreditAccount(std::string owner, double balance, double interest_rate) : BankAccount(std::move(owner), balance), _interest_rate(normalize_rate(interest_rate)) {}

    /**
     * @brief Возвращает годовую процентную ставку.
     * @return Ставка в процентах.
     */
    [[nodiscard]] double get_interest_rate() const override { return _interest_rate; }

    /**
     * @brief Возвращает тип счёта.
     * @return Строковое представление типа ("Кредитный").
     */
    [[nodiscard]] std::string_view get_type() const override { return "Кредитный"; }

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

        const double monthly_rate = (_interest_rate / 100.0) / 12.0;
        const double interest_amount = std::abs(get_balance()) * monthly_rate;

        set_balance(get_balance() - interest_amount);
    }
};

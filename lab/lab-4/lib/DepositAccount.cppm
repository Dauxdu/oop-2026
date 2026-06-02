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
    double _interest_rate{};

    /**
     * @brief Нормализует процентную ставку, гарантируя, что она неотрицательна.
     * @param[in] interest_rate Исходная процентная ставка.
     * @return Неотрицательное значение ставки (минимум 0.0).
     */
    double normalize_rate(double interest_rate) { return std::max(0.0, interest_rate); }

public:
    /**
     * @brief Конструктор вкладового счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     * @param[in] interest_rate Годовая процентная ставка. Отрицательные значения заменяются на 0.0.
     */
    DepositAccount(std::string owner, double balance, double interest_rate) : BankAccount(std::move(owner), balance), _interest_rate(normalize_rate(interest_rate)) {}

    /**
     * @brief Возвращает годовую процентную ставку.
     * @return Ставка в процентах.
     */
    [[nodiscard]] double get_interest_rate() const override { return _interest_rate; }

    /**
     * @brief Возвращает тип счёта.
     * @return Строковое представление типа ("Вкладовый").
     */
    [[nodiscard]] std::string_view get_type() const override { return "Вкладовый"; }

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

        const double monthly_rate = (_interest_rate / 100.0) / 12.0;
        const double interest_amount = get_balance() * monthly_rate;

        set_balance(get_balance() + interest_amount);
    }
};

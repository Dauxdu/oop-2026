/**
 * @file CheckingAccount.cppm
 * @brief Реализация расчётного банковского счёта.
 */
export module BankAccounts:CheckingAccount;

import std;
import :BankAccount;

/**
 * @brief Расчётный счёт (без процентов).
 * @details Наследуется от BankAccount. Метод начисления процентов переопределён
 *          как пустая операция, так как для данного типа счёта проценты не предусмотрены.
 */
export class CheckingAccount final : public BankAccount
{
public:
    /**
     * @brief Конструктор расчётного счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     */
    CheckingAccount(std::string owner, double balance) : BankAccount(std::move(owner), balance) {}

    /**
     * @brief Возвращает тип счёта.
     * @return Строковое представление типа ("Расчётный").
     */
    [[nodiscard]] std::string_view get_type() const override { return "Расчётный"; }

    /**
     * @brief Начисление процентов.
     * @note Для расчётного счёта операция не выполняется.
     */
    void apply_monthly_interest() override {}
};

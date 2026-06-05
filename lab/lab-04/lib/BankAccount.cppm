/**
 * @file BankAccount.cppm
 * @brief Базовый абстрактный класс банковского счёта.
 */
export module BankAccounts:BankAccount;

import std;

/**
 * @brief Абстрактный базовый класс банковского счёта.
 * @details Определяет общий интерфейс для всех типов счетов (расчётный, кредитный, вкладовый).
 */
export class BankAccount
{
private:
    std::string _owner;
    double _balance{};

protected:
    /**
     * @brief Устанавливает баланс.
     * @param[in] balance Новый баланс.
     */
    void set_balance(double balance)
    {
        _balance = balance;
    }

public:
    virtual ~BankAccount() = default;
    BankAccount() = delete;
    BankAccount(const BankAccount &) = delete;
    BankAccount &operator=(const BankAccount &) = delete;

    /**
     * @brief Конструктор счёта.
     * @param[in] owner ФИО владельца.
     * @param[in] balance Начальный баланс.
     * @throws std::invalid_argument Если имя владельца пустое.
     */
    BankAccount(std::string owner, double balance) : _owner(std::move(owner)), _balance(balance)
    {
        if (_owner.empty())
        {
            throw std::invalid_argument("Имя владельца не может быть пустым");
        }
    }

    /// @brief Получить владельца.
    /// @return Константная ссылка на ФИО владельца.
    const std::string &get_owner() const { return _owner; }

    /// @brief Получить баланс.
    /// @return Текущий баланс счёта.
    double get_balance() const { return _balance; }

    /// @brief Годовая процентная ставка (%).
    /// @return Годовая ставка в процентах (0.0 по умолчанию).
    virtual double get_interest_rate() const { return 0.0; }

    /// @brief Тип счёта.
    /// @return Строковое представление типа счёта.
    virtual std::string_view get_type() const = 0;

    /// @brief Начисляет проценты за месяц.
    virtual void apply_monthly_interest() = 0;
};

export using AccountPtr = std::unique_ptr<BankAccount>;

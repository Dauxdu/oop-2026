/**
 * @file bank.ixx
 * @brief Основной интерфейс модуля bank.
 * @details Экспортирует компоненты счёта (BankAccount) и алгоритмы
 *          их обработки (BankAccountAlgorithms) как единый модуль.
 */
export module bank;

export import :BankAccount;
export import :BankAccountAlgorithms;
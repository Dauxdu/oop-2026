/**
 * @file vector.cppm
 * @brief Модуль с алгоритмами для заполнения и агрегации векторов.
 * @details Содержит функции для генерации случайных данных и математических
 *          операций над контейнерами std::vector.
 */
export module Vector;

import std;

/**
 * @brief Заполняет вектор случайными числами в диапазоне [min_value, max_value].
 * @param[in, out] vec        Вектор для заполнения.
 * @param[in]      min_value  Минимальное значение (включительно).
 * @param[in]      max_value  Максимальное значение (включительно).
 * @throws std::logic_error Если min_value > max_value.
 */
export void fill_random(std::vector<int> &vec, int min_value, int max_value)
{
    if (min_value > max_value)
    {
        throw std::logic_error("Минимальное значение должно быть меньше максимального.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_value, max_value);

    for (int &x : vec)
    {
        x = dist(gen);
    }
}

/**
 * @brief Вычисляет арифметическую сумму элементов вектора.
 * @param[in] vec Вектор для суммирования.
 * @return Сумма элементов.
 */
export int calculate_sum(const std::vector<int> &vec)
{
    int sum{};
    for (const int &x : vec)
    {
        sum += x;
    }

    return sum;
}
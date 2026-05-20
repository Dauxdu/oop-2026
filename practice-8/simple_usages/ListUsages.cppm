export module simple_usages:ListUsages;

import std;
import containers;

export void list_simple_usages()
{
    List<int> numbers;

    numbers.Add(-21);
    numbers.Add(21);
    numbers.Add(-21);
    numbers.Add(105);

    numbers.Insert(1, 502);

    std::println("Количество чисел: {}", numbers.Count());

    if (!numbers.Contains(100))
    {
        std::println("100 не содержится в списке чисел");
    }

    try
    {
        std::println("Первое число: {}", numbers[0]);
    }
    catch (const std::out_of_range &err)
    {
        std::cerr << "Ошибка доступа: " << err.what() << "\n";
        std::exit(-1);
    }

    if (numbers.Remove(-21))
    {
        std::println("Число -21 удалено");
    }

    numbers.RemoveAt(1);

    numbers.SetCapacity(100);
    std::println("Текущий размер списка чисел: {}", numbers.Capacity());

    std::println("Все числа:");
    auto enumerator = numbers.GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto &value = enumerator->Current();
        std::println("Значение: {}", value);
    }

    numbers.Clear();
    std::println("Список чисел очищен: {}, Текущий размер списка: {}", numbers.Count(), numbers.Capacity());
}
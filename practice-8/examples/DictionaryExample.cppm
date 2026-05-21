export module examples:DictionaryExample;

import std;
import containers;

export void dictionary_example()
{
    std::println("\n--------------------------------");
    std::println("Dictionary Example");

    Dictionary<std::string, unsigned int> journal;

    journal.Add({"Маша", 18});
    journal.Add({"Никита", 23});
    journal.Add({"Максим", 18});
    journal.Add({"Максим", 19});

    std::println("Количество записей в журнале: {}", journal.Count());

    if (journal.Contains({"Маша", 18}))
    {
        std::println("Маша уже внесена в журнал в журнал");
    }

    try
    {
        std::println("Возраст Максима: {}", journal["Максим"]);
    }
    catch (const std::out_of_range &err)
    {
        std::cerr << "Ошибка доступа: " << err.what() << "\n";
        std::exit(-1);
    }

    if (journal.Remove({"Никита", 23}))
    {
        std::println("Никита снят с учёта");
    }

    journal.SetCapacity(100);
    std::println("Текущий размер журнала: {}", journal.Capacity());

    std::println("Все записи в журнале:");
    auto enumerator = journal.GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto &[key, value] = enumerator->Current();
        std::println("Имя: {}, Возраст: {}", key, value);
    }

    journal.Clear();
    std::println("Журнал очищен: {}, Текущей размер журнала: {}", journal.Count(), journal.Capacity());
    std::println("--------------------------------\n");
}
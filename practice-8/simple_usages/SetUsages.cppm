export module simple_usages:SetUsages;

import std;
import containers;

export void set_example()
{
    std::println("\n--------------------------------");
    std::println("Set Example");

    HashSet<std::string> nicknames;

    nicknames.Add("CherryJelly");
    nicknames.Add("dauxdu");
    nicknames.Add("snxp3rr");
    nicknames.Add("CherryJelly");

    std::println("Количество псевдонимов: {}", nicknames.Count());

    if (nicknames.Contains("dauxdu"))
    {
        std::println("Данный псевдоним уже существует");
    }

    if (nicknames.Remove("CherryJelly"))
    {
        std::println("Псевдоним CherryJelly удалён");
    }

    nicknames.SetCapacity(100);
    std::println("Текущий размер коллекции псевдонимов: {}", nicknames.Capacity());

    std::println("Все записанные псевдонимы:");
    auto enumerator = nicknames.GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto &nickname = enumerator->Current();
        std::println("Псевдоним: {}", nickname);
    }

    nicknames.Clear();
    std::println("Коллекция псевдонимов очищена: {}, Текущий размер коллекции псевдонимов: {}", nicknames.Count(), nicknames.Capacity());
    std::println("--------------------------------\n");
}
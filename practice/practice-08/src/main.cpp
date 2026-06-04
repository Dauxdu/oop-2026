import std;
import containers;

void dictionary_example()
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
        std::println("Маша уже внесена в журнал");
    }

    try
    {
        std::println("Возраст Максима: {}", journal["Максим"]);
    }
    catch (const std::out_of_range &err)
    {
        std::println(std::cerr, "Ошибка доступа: {}", err.what());
        throw;
    }

    if (journal.Remove({"Никита", 23}))
    {
        std::println("Никита снят с учёта");
    }

    journal.SetCapacity(100);
    std::println("Текущий размер журнала (bucket_count): {}", journal.Capacity());

    std::println("Все записи в журнале:");
    auto enumerator = journal.GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto &[key, value] = enumerator->Current();
        std::println("Имя: {}, Возраст: {}", key, value);
    }

    journal.Clear();
    std::println("Журнал очищен. Записей: {}, Размер (bucket_count): {}", journal.Count(), journal.Capacity());
    std::println("--------------------------------\n");
}

void hashset_example()
{
    std::println("\n--------------------------------");
    std::println("HashSet Example");

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

void list_example()
{
    std::println("\n--------------------------------");
    std::println("List Example");

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
    std::println("--------------------------------\n");
}

void queue_example()
{
    std::println("\n--------------------------------");
    std::println("Queue Example");

    Queue<int> queue;
    queue.Enqueue(10);
    queue.Enqueue(1);
    queue.Enqueue(20);

    auto enumerator = queue.GetEnumerator();
    std::println("Enumeration:");
    while (enumerator->MoveNext())
    {
        std::println("  Current: {}", enumerator->Current());
    }

    std::println("\nPost-enumeration operations:");
    std::println("  Dequeue() → {}", queue.Dequeue());
    std::println("  Peek()    → {}", queue.Peek());
    std::println("  Count     → {}", queue.Count());

    std::println("--------------------------------\n");
}

void stack_example()
{
    std::println("\n--------------------------------");
    std::println("Stack Example");

    Stack<int> stack;

    stack.Push(10);
    stack.Push(1);
    stack.Push(20);

    auto enumerator = stack.GetEnumerator();

    std::println("Enumeration:");
    while (enumerator->MoveNext())
    {
        std::println("  Current: {}", enumerator->Current());
    }

    std::println("\nPost-enumeration operations:");
    std::println("  Pop()  → {}", stack.Pop());
    std::println("  Peek() → {}", stack.Peek());
    std::println("  Count  → {}", stack.Count());
    std::println("--------------------------------\n");
}

int main()
{
    dictionary_example();
    hashset_example();
    list_example();
    queue_example();
    stack_example();

    return 0;
}
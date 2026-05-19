import std;

void print_range_and_count()
{
    std::println("9. Даны два целых числа a и b (a < b). Вывести все целые числа от a до b и их количество.");

    int a = 0;
    int b = 0;

    std::print("Введите a и b (a < b): ");
    if (!(std::cin >> a >> b) || a >= b)
    {
        std::println("Ошибка ввода. Убедитесь, что a < b.");
        return;
    }

    std::print("Числа: ");
    std::size_t count = 0;
    for (int i = a; i <= b; ++i)
    {
        std::print("{} ", i);
        ++count;
    }
    std::println("\nКоличество чисел: {}", count);
}

void powers_of_number()
{
    std::println("10. Дано вещественное число a и целое число n > 0. Вывести целые степени a от 1 до n.");

    double a = 0;
    std::size_t n = 0;
    std::print("Введите a и n (n > 0): ");

    std::cin >> a >> n;

    double current_power = a;
    for (std::size_t i = 1; i <= n; ++i)
    {
        std::println("{}^{} = {}", a, i, current_power);
        current_power *= a;
    }
}

int main()
{
    print_range_and_count();
    std::println();
    powers_of_number();

    return 0;
}
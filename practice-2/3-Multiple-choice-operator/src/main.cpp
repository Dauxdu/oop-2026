import std;

void number_to_words()
{
    std::println("8. Дано целое число в диапазоне 100-999. Вывести строку-описание.");

    int n = 0;
    std::print("Введите число (100-999): ");

    if (!(std::cin >> n) || n < 100 || n > 999)
    {
        std::println("Ошибка: введите целое число в диапазоне 100-999");
        return;
    }

    const std::string hundreds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    const std::string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    const std::string units[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    const std::string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};

    const int h = n / 100;
    const int t = (n / 10) % 10;
    const int u = n % 10;

    std::string result = std::string(hundreds[h]);

    if (t == 1)
    {
        result += " " + std::string(teens[u]);
    }
    else
    {
        if (t > 1)
        {
            result += " " + std::string(tens[t]);
        }
        if (u > 0)
        {
            result += " " + std::string(units[u]);
        }
    }

    std::println("{}", result);
}

int main()
{
    number_to_words();
    return 0;
}
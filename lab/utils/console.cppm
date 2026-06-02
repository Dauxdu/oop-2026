export module console;

import std;

export void print_header(int lab_num)
{
    std::println("-----------------------------------------------");
    std::println("Лабораторная работа №{}", lab_num);
    std::println("Вариант: 1");
    std::println("Группа: 6112-100503D");
    std::println("Автор: Агапов Н.А.");
    std::println("-----------------------------------------------");
}

export std::string get_system_username()
{
    if (const char *username = std::getenv("USER"))
    {
        return username;
    }

    if (const char *username = std::getenv("USERNAME"))
    {
        return username;
    }

    return "Пользователь";
}

export void clear_input_buffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

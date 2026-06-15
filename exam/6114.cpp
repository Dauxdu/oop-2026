import std;

class Human
{
private:
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    int _birth_year{};

public:
    Human(std::string surname, std::string name, std::string patronymic, int birth_year)
        : _surname(surname), _name(name), _patronymic(patronymic), _birth_year(birth_year) {}

    std::string get_initials() const
    {
        return std::format("{}.{}.{}.", _surname.front(), _name.front(), _patronymic.front());
    }

    int get_age(int current_year) const
    {
        return current_year - _birth_year;
    }
};

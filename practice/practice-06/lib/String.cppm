export module String;
import std;

export class String
{
private:
    char *_str = nullptr;
    std::size_t _size = 0;

    void assign(const char *str)
    {
        if (!str)
        {
            str = "";
        }

        _size = std::strlen(str);
        char *new_str = new char[_size + 1];
        std::strcpy(new_str, str);

        delete[] _str;
        _str = new_str;
    }

public:
    // 1. Конструктор по умолчанию
    String() { assign(""); }

    // 2. Конструктор по Cи-строке
    String(const char *str) { assign(str); }

    // 3. Деструктор
    ~String() { delete[] _str; }

    // 4. Конструктор копирования
    String(const String &other) { assign(other._str); }

    // 5. Конструктор перемещения
    String(String &&other) : _str(other._str), _size(other._size)
    {
        other._str = nullptr;
        other._size = 0;
    }

    // 6. Оператор присваивания копированием
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            assign(other._str);
        }

        return *this;
    }

    // 7. Оператор присваивания перемещением
    String &operator=(String &&other)
    {
        if (this != &other)
        {
            delete[] _str;
            _str = other._str;
            _size = other._size;

            other._str = nullptr;
            other._size = 0;
        }

        return *this;
    }

    // Метод для получения размера строки
    std::size_t size() const { return _size; }

    // Факультатив, вместо операторов []
    template <typename TString>
    auto &&operator[](this TString &&self, std::size_t index)
    {
        return std::forward<TString>(self)._str[index];
    }

    const char *str() const { return _str ? _str : ""; }
};

namespace std
{
    template <>
    struct formatter<String, char>
    {
        constexpr auto parse(std::format_parse_context &ctx)
        {
            auto it = ctx.begin();
            while (it != ctx.end() && *it != '}')
            {
                ++it;
            }

            return it;
        }

        auto format(const String &str, std::format_context &ctx) const
        {
            auto out = ctx.out();
            for (std::size_t i = 0; i < str.size(); ++i)
            {
                *out++ = str[i];
            }

            return out;
        }
    };
}

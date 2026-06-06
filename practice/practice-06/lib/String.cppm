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
    ~String() { delete[] _str; }
    String() { assign(""); }
    String(const char *str) { assign(str); }
    String(const String &other) { assign(other._str); }

    String(String &&other) : _str(other._str), _size(other._size)
    {
        other._str = nullptr;
        other._size = 0;
    }

    String &operator=(String other)
    {
        std::swap(_str, other._str);
        std::swap(_size, other._size);

        return *this;
    }

    template <typename Self>
    auto &&operator[](this Self &&self, std::size_t index)
    {
        return std::forward<Self>(self)._str[index];
    }

    std::size_t size() const { return _size; }

    const char *str() const { return _str ? _str : ""; }
};
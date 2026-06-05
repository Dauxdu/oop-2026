export module String;
import std;

export class String
{
private:
    char *_s = nullptr;
    std::size_t _size = 0;

    void assign(const char *s)
    {
        if (!s)
        {
            s = {};
        }

        std::size_t new_size = std::strlen(s);

        char *new_s = new char[new_size + 1];
        std::strcpy(new_s, s);

        delete[] _s;
        _s = new_s;
        _size = new_size;
    }

public:
    ~String() { delete[] _s; }
    String() {}
    String(const char *s) { assign(s); }
    String(const String &other) { assign(other._s); }

    String(String &&other) : _s(other._s), _size(other._size)
    {
        other._s = nullptr;
        other._size = 0;
    }

    String &operator=(String other)
    {
        std::swap(_s, other._s);
        std::swap(_size, other._size);

        return *this;
    }

    template <typename Self>
    auto &&operator[](this Self &&self, std::size_t index)
    {
        return std::forward<Self>(self)._s[index];
    }

    std::size_t size() const { return _size; }

    const char *str() const { return _s ? _s : ""; }
};
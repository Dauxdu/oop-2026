export module StringBuilder;
import std;

export class StringBuilder
{
private:
    std::string _buffer;

public:
    // Правило нуля
    StringBuilder() = default;

    // Резервирование памяти
    void reserve(std::size_t bytes) { _buffer.reserve(bytes); }

    // Перегрузка append const std::string&
    StringBuilder &append(const std::string &str)
    {
        _buffer.append(str);
        return *this;
    }

    // Перегрузка append int
    StringBuilder &append(const int num)
    {
        _buffer.append(std::to_string(num));
        return *this;
    }

    // Перегрузка append float
    StringBuilder &append(const float num)
    {
        _buffer.append(std::to_string(num));
        return *this;
    }

    // lvalue
    std::string build() const & { return _buffer; }

    // rvalue
    std::string build() && { return std::move(_buffer); }

    // Остальная логика
    std::size_t size() const { return _buffer.size(); }

    std::size_t capacity() const { return _buffer.capacity(); }

    std::string str() const { return _buffer; }
};
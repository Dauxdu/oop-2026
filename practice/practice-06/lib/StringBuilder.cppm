export module StringBuilder;
import std;

export class StringBuilder
{
private:
    std::string _buffer;

public:
    StringBuilder() = default;

    void reserve(std::size_t bytes) { _buffer.reserve(bytes); }

    StringBuilder &append(const std::string &str)
    {
        _buffer.append(str);
        return *this;
    }

    StringBuilder &append(const int num)
    {
        _buffer.append(std::to_string(num));
        return *this;
    }

    StringBuilder &append(const float num)
    {
        _buffer.append(std::to_string(num));
        return *this;
    }

    std::string build() const & { return _buffer; }

    std::string build() && { return std::move(_buffer); }

    std::size_t size() const { return _buffer.size(); }

    std::size_t capacity() const { return _buffer.capacity(); }

    std::string str() const { return _buffer; }
};
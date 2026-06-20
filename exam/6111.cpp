import std;

// Как был реализован IVec - неизвестно
class IVec
{
public:
    virtual ~IVec() = default;
    virtual float Get(std::size_t i) const = 0;
    virtual void Set(std::size_t i, float value) = 0;
    virtual std::size_t Size() const = 0;
};

class Vec final : public IVec
{
private:
    std::vector<float> _vec;

public:
    explicit Vec(std::size_t n)
    {
        if (n == 0)
        {
            throw std::invalid_argument("Vector size must be greater than 0");
        }

        _vec.resize(n);
    }

    float Get(std::size_t i) const override
    {
        if (i >= _vec.size())
        {
            throw std::out_of_range("Index out of range");
        }

        return _vec[i];
    }

    void Set(std::size_t i, float value) override
    {
        if (i >= _vec.size())
        {
            throw std::out_of_range("Index out of range");
        }

        _vec[i] = value;
    }

    std::size_t Size() const override
    {
        return _vec.size();
    }
};

float CalculateNorm(const Vec &vec)
{
    float result{};
    for (std::size_t i = 0; i < vec.Size(); ++i)
    {
        result += std::abs(vec.Get(i));
    }

    return result;
}

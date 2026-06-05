export module implementations:user;

import std;
import api;
import universal_value;

export class User final : public Serializable
{
private:
    std::string _name;
    std::size_t _age{};

public:
    User() = default;

    User(std::string name, int age)
        : _name(std::move(name)), _age(age) {}

    Value to_value() const override
    {
        return Value(ObjectValue{
            {"name", _name},
            {"age", static_cast<double>(_age)}});
    }

    const std::string &name() const
    {
        return _name;
    }

    std::size_t age() const
    {
        return _age;
    }
};
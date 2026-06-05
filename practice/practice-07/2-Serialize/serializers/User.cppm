export module serializers:User;

import std;
import api;
import UValue;

export class User final : public Serializable
{
private:
    std::string _name;
    double _age{};

public:
    User() = default;
    User(std::string name, double age) : _name(std::move(name)), _age(age) {}

    UValue to_value() const override
    {
        return UValue(ObjectValue{
            {"name", _name},
            {"age", _age}});
    }

    const std::string &get_name() const { return _name; }

    double get_age() const { return _age; }
};
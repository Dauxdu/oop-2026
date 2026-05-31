export module universal_value;

import std;

export struct Value;

export using ArrayValue = std::vector<Value>;
export using ObjectValue = std::unordered_map<std::string, Value>;

export struct Value
{
    std::variant<std::nullptr_t, bool, double, std::string, ArrayValue, ObjectValue> v;

    Value() = default;
    Value(std::nullptr_t n) : v(n) {}
    Value(bool b) : v(b) {}
    Value(double d) : v(d) {}
    Value(std::string s) : v(std::move(s)) {}
    Value(ArrayValue a) : v(std::move(a)) {}
    Value(ObjectValue o) : v(std::move(o)) {}
};
export module UValue;

import std;

export struct UValue;

export using ArrayValue = std::vector<UValue>;
export using ObjectValue = std::unordered_map<std::string, UValue>;

export struct UValue
{
    std::variant<std::nullptr_t, bool, double, std::string, ArrayValue, ObjectValue> _v;

    UValue() = default;
    UValue(std::nullptr_t n) : _v(n) {}
    UValue(bool b) : _v(b) {}
    UValue(double d) : _v(d) {}
    UValue(std::string s) : _v(std::move(s)) {}
    UValue(const char *s) : _v(std::string(s)) {}
    UValue(ArrayValue a) : _v(std::move(a)) {}
    UValue(ObjectValue o) : _v(std::move(o)) {}
};

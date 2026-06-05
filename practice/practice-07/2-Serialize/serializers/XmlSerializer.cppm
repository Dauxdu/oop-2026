export module serializers:XmlSerializer;

import std;
import api;
import UValue;

export class XmlSerializer final : public Serializer
{
private:
    std::string _root_name;

    static std::string escape(const char &c)
    {
        switch (c)
        {
        case '&':
            return "&amp;";
        case '<':
            return "&lt;";
        case '>':
            return "&gt;";
        case '"':
            return "&quot;";
        case '\'':
            return "&apos;";
        default:
            return std::string(1, c);
        }
    }

    static std::string to_element(const UValue &value, std::string_view tag)
    {
        std::string result = "<" + std::string(tag) + ">";
        if (auto *s = std::get_if<std::string>(&value._v))
        {
            for (char c : *s)
            {
                result += escape(c);
            }
        }
        else if (auto *d = std::get_if<double>(&value._v))
        {
            result += std::to_string(*d);
        }
        else if (auto *b = std::get_if<bool>(&value._v))
        {
            result += *b ? "true" : "false";
        }
        else if (auto *a = std::get_if<ArrayValue>(&value._v))
        {
            for (auto &x : *a)
            {
                result += to_element(x, "item");
            }
        }
        else if (auto *o = std::get_if<ObjectValue>(&value._v))
        {
            for (auto &[key, x] : *o)
            {
                result += to_element(x, key);
            }
        }

        return result + "</" + std::string(tag) + ">";
    }

public:
    explicit XmlSerializer(std::string root_name = "null") : _root_name(std::move(root_name)) {}

    std::string serialize(const UValue &value) const override { return to_element(value, _root_name); }
};
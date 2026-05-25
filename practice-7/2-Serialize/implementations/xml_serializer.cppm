export module implementations:xml_serializer;

import std;
import api;
import universal_value;

export class XmlSerializer final : public Serializer
{
public:
    explicit XmlSerializer(std::string root_name = "null")
        : _root_name(std::move(root_name)) {}

    std::string serialize(const Value &value) const override
    {
        return to_element(value, _root_name);
    }

private:
    std::string _root_name;

    static std::string escape(const char &c)
    {
        switch (c)
        {
        case '&':
        {
            return "&amp;";
        }
        case '<':
        {
            return "&lt;";
        }
        case '>':
        {
            return "&gt;";
        }
        case '"':
        {
            return "&quot;";
        }
        case '\'':
        {
            return "&apos;";
        }
        default:
        {
            return std::string(1, c);
        }
        }
    }

    static std::string to_element(const Value &value, std::string_view tag)
    {
        std::string result = "<" + std::string(tag) + ">";
        if (auto *s = std::get_if<std::string>(&value.v))
        {
            for (char c : *s)
            {
                result += escape(c);
            }
        }
        else if (auto *d = std::get_if<double>(&value.v))
        {
            result += std::to_string(*d);
        }
        else if (auto *b = std::get_if<bool>(&value.v))
        {
            if (*b)
            {
                result += "true";
            }
            result += "false";
        }
        else if (auto *a = std::get_if<ArrayValue>(&value.v))
        {
            for (auto &x : *a)
            {
                result += to_element(x, "item");
            }
        }
        else if (auto *o = std::get_if<ObjectValue>(&value.v))
        {
            for (auto &[key, x] : *o)
            {
                result += to_element(x, key);
            }
        }
        return result + "</" + std::string(tag) + ">";
    }
};
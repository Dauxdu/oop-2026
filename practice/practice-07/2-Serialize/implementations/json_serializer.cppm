export module implementations:json_serializer;

import std;
import api;
import universal_value;

export class JsonSerializer final : public Serializer
{
public:
    std::string serialize(const Value &value) const override
    {
        return to_string(value);
    }

private:
    static std::string escape(std::string_view string)
    {
        std::string result = "\"";
        for (char c : string)
        {
            if (c == '"' || c == '\\')
            {
                result += '\\';
            }
            result += c;
        }
        return result + "\"";
    }

    static std::string to_string(const Value &value)
    {
        if (std::holds_alternative<std::nullptr_t>(value.v))
        {
            return "";
        }
        if (auto *b = std::get_if<bool>(&value.v))
        {
            if (*b)
            {
                return "true";
            }
            return "false";
        }
        if (auto *d = std::get_if<double>(&value.v))
        {
            return std::to_string(*d);
        }
        if (auto *s = std::get_if<std::string>(&value.v))
        {
            return escape(*s);
        }
        if (auto *a = std::get_if<ArrayValue>(&value.v))
        {
            std::string result = "[";
            bool first = true;
            for (std::size_t i = 0; i < (*a).size(); ++i)
            {
                if (!first)
                {
                    result += ",";
                }
                first = false;
                result += to_string((*a).at(i));
            }
            return result + "]";
        }
        if (auto *o = std::get_if<ObjectValue>(&value.v))
        {
            std::string result = "{";
            bool first = true;
            for (auto &[key, x] : *o)
            {
                if (!first)
                {
                    result += ",";
                }
                first = false;
                result += "\"" + key + "\":" + to_string(x);
            }
            return result + "}";
        }
        return "";
    }
};
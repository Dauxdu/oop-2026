export module serializers:JsonSerializer;

import std;
import api;
import UValue;

export class JsonSerializer final : public Serializer
{
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

    static std::string to_string(const UValue &value)
    {
        if (std::holds_alternative<std::nullptr_t>(value._v))
        {
            return "null";
        }

        if (auto *b = std::get_if<bool>(&value._v))
        {
            return *b ? "true" : "false";
        }

        if (auto *d = std::get_if<double>(&value._v))
        {
            return std::to_string(*d);
        }

        if (auto *s = std::get_if<std::string>(&value._v))
        {
            return escape(*s);
        }

        if (auto *a = std::get_if<ArrayValue>(&value._v))
        {
            std::string result = "[";
            bool first = true;
            for (const auto &item : *a)
            {
                if (!first)
                {
                    result += ",";
                }

                first = false;
                result += to_string(item);
            }

            return result + "]";
        }

        if (auto *o = std::get_if<ObjectValue>(&value._v))
        {
            std::string result = "{";
            bool first = true;
            for (auto &[key, item] : *o)
            {
                if (!first)
                {
                    result += ",";
                }

                first = false;
                result += std::format("\"{}\":{}", key, to_string(item));
            }

            return result + "}";
        }

        return "";
    }

public:
    std::string serialize(const UValue &value) const override { return to_string(value); }
};
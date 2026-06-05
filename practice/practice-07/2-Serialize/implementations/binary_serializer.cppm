export module implementations:binary_serializer;

import std;
import api;
import universal_value;

export class BinarySerializer final : public Serializer
{
public:
    std::string serialize(const Value &value) const override
    {
        std::string out;
        to_bin(value, out);
        return out;
    }

private:
    static void to_bin(const Value &value, std::string &out)
    {
        if (std::holds_alternative<std::nullptr_t>(value.v))
        {
            out += '\0';
        }
        else if (auto *b = std::get_if<bool>(&value.v))
        {
            out += '\1';
            if (*b)
            {
                out += '\1';
            }
            out += '\0';
        }
        else if (auto *d = std::get_if<double>(&value.v))
        {
            out += '\2';
            out.append((const char *)d, 8);
        }
        else if (auto *s = std::get_if<std::string>(&value.v))
        {
            std::uint32_t length = static_cast<std::uint32_t>((*s).size());
            out += '\3';
            out.append((const char *)&length, 4);
            out += *s;
        }
        else if (auto *a = std::get_if<ArrayValue>(&value.v))
        {
            std::uint32_t length = static_cast<std::uint32_t>((*a).size());
            out += '\4';
            out.append((const char *)&length, 4);
            for (auto &x : *a)
            {
                to_bin(x, out);
            }
        }
        else if (auto *o = std::get_if<ObjectValue>(&value.v))
        {
            std::uint32_t length = static_cast<std::uint32_t>((*o).size());
            out += '\5';
            out.append((const char *)&length, 4);
            for (auto &[key, x] : *o)
            {
                std::uint32_t key_length = static_cast<std::uint32_t>(key.size());
                out.append((const char *)&key_length, 4);
                out += key;
                to_bin(x, out);
            }
        }
    }
};
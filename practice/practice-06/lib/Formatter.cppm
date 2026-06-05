export module Formatter;
import std;
import String;

export namespace std
{
    template <>
    struct formatter<String, char>
    {
        constexpr auto parse(format_parse_context &ctx)
        {
            auto it = ctx.begin();
            while (it != ctx.end() && *it != '}')
            {
                ++it;
            }

            return it;
        }

        auto format(const String &p, format_context &ctx) const
        {
            std::string_view sv = p.str();
            return std::copy(sv.begin(), sv.end(), ctx.out());
        }
    };
}
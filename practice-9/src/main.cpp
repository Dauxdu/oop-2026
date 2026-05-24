#include <httplib.h>
import std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::println("Использование: {} <URL>", argv[0]);
        return 1;
    }

    std::string url = argv[1];

    if (!url.starts_with("http://") && !url.starts_with("https://"))
    {
        url = "http://" + url;
    }

    httplib::Client cli(url);
    cli.set_follow_location(true);

    if (auto result = cli.Get("/"))
    {
        std::println("HTTP Status: {}\n", result->status);

        for (const auto &[key, value] : result->headers)
        {
            std::println("{}: {}", key, value);
        }
    }
    else
    {
        std::println("Ошибка: {}", httplib::to_string(result.error()));
        return 1;
    }

    return 0;
}
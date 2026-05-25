import std;

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::println("Привет, {}", argv[1]);
    }
    else
    {
        std::println("Привет, {}", std::getenv("USERNAME"));
    }

    return 0;
}
import std;

std::vector<int> Make(const int a, const int b)
{
    std::vector<int> vec;

    for (int i = a; i <= b; ++i)
    {
        vec.emplace_back(i);
    }

    return vec;
}

void Print(const std::vector<int> &vec)
{
    std::println("{}", vec);
}

int main()
{
    int a{};
    int b{};

    std::cin >> a >> b;

    std::vector<int> vec = Make(a, b);
    Print(vec);

    return 0;
}

import std;

int main()
{
	std::println("Введите трехзначное число:");
	int num = 0;
	std::cin >> num;
	bool res = 0;
	res = ((num / 100) < (num % 100 / 10)) && ((num % 100 / 10) < (num % 10));
	std::println("{}", res);
	return 0;
}
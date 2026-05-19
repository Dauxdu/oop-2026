import std;

int main()
{
	std::println("Введите день от 1 до 365: ");
	int n = 0;
	std::cin >> n;
	std::println("Введите день недели, с которой начинается год ");
	int k = 0;
	std::cin >> k;

	int day = (n - 1) + k - 1;
	day %= 7;
	day += 1;

	std::println("Сегодня день недели: {}", day);

	return 0;
}
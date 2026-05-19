import std;

// 1
int main1()
{
	int number;
	std::println("Введите трёхначное число:");
	std::cin >> number;
	int hund = number / 100;
	int ten = number % 100 / 10;
	int one = number % 10;
	int sum = hund + ten + one;
	int mul = hund * ten * one;
	std::println("Сумма: {} \n Произведние: {}", sum, mul);
	return 0;
}

// 2
int main2()
{
	int current_time = 0;
	std::println("Введите текущее время(в секундах)");
	std::cin >> current_time;
	int seconds = 0;
	seconds = current_time % 3600;
	std::println("С начала последнего часа прошло: {} секунд", seconds);
	return 0;
}

// 3
int main3()
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

// 4
int main4()
{
	std::println("Введите трехзначное число:");
	int num = 0;
	std::cin >> num;
	bool res = 0;
	res = ((num / 100) < (num % 100 / 10)) && ((num % 100 / 10) < (num % 10));
	std::println("{}", res);
	return 0;
}

// 5
int main5()
{
	int x1, x2, y1, y2;
	std::println("введите клетку, на которой стоит ладья (x1,y1):");
	std::cin >> x1 >> y1;
	std::println("введите клетку, в которую перейдёт ладья (x2,y2):");
	std::cin >> x2 >> y2;
	bool result(x1 == x2 || y1 == y2);
	std::println("{}", result);
	return 0;
}

int main()
{
	main1();
	main2();
	main3();
	main4();
	main5();
	return 0;
}
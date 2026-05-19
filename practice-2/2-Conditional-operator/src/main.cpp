import std;

void days_in_year()
{
	std::println("6. Дан номер года. Определить количество дней в этом году.");

	int year = 0;
	std::print("Введите год: ");
	if (!(std::cin >> year) || year <= 0)
	{
		std::println("Ошибка ввода. Год должен быть положительным целым числом.");
		return;
	}

	bool is_leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	std::println("В году {} {} дней.", year, is_leap ? 366 : 365);
}

void describe_number()
{
	std::println("7. Дано целое число из диапазона 1-999. Вывести его строку-описание.");

	int num = 0;
	std::print("Введите число (1-999): ");
	if (!(std::cin >> num) || num < 1 || num > 999)
	{
		std::println("Ошибка ввода. Число должно быть в диапазоне 1-999.");
		return;
	}

	std::string parity = (num % 2 == 0) ? "четное" : "нечетное";
	int digits = (num >= 100) ? 3 : (num >= 10) ? 2
												: 1;
	std::string digit_str;

	switch (digits)
	{
	case 1:
		digit_str = "однозначное";
		break;
	case 2:
		digit_str = "двузначное";
		break;
	case 3:
		digit_str = "трехзначное";
		break;
	}

	std::println("{} {} число", parity, digit_str);
}

int main()
{
	days_in_year();
	std::println();
	describe_number();

	return 0;
}
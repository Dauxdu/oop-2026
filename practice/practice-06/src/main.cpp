import std;
import String;
import Formatter;
import StringBuilder;

int main()
{
	char st[] = "привет, мир!";

	String str(st);
	std::println("{}", str);

	String str1(str);
	std::println("str1: {}", str1);

	String str2 = str1;
	std::println("str2: {}", str2);

	String str3(std::move(str1));
	std::println("str3: {}", str3);

	String str4 = std::move(str2);
	std::println("str4: {}", str4);

	std::println("str1 new: {}", str1);
	std::println("str2 new: {}", str2);

	std::println("---------------------------------------------------");
	StringBuilder s1;
	std::size_t size{};
	std::println("Введите объем памяти:");

	if (!(std::cin >> size))
	{
		return 1;
	}

	s1.reserve(size);

	int choice{};
	while (true)
	{
		std::println("Выберите действие: (1) Добавить строку, (2) Добавить int, (3) Добавить float, (4) Выход");
		if (!(std::cin >> choice))
		{
			break;
		}

		if (choice == 4)
		{
			break;
		}

		switch (choice)
		{
		case 1:
		{
			std::println("Введите строку:");
			std::string s_1;
			std::getline(std::cin, s_1);
			s1.append(s_1);

			break;
		}
		case 2:
		{
			std::println("Введите целочисленное значение:");
			int s_1;

			if (std::cin >> s_1)
			{
				s1.append(s_1);
			}

			break;
		}
		case 3:
		{
			std::println("Введите float:");
			float s_1;
			if (std::cin >> s_1)
			{
				s1.append(s_1);
			}

			break;
		}
		default:
			std::println("Неверный выбор!");

			break;
		}
	}

	std::println("Емкость:{} Размер:{} Строка:{}", s1.capacity(), s1.size(), s1.str());

	StringBuilder s2;
	s2 = s1;
	std::println("s1: {}, s2: {}", s1.str(), s2.str());

	std::string string1 = s1.build();
	std::string string2 = std::move(s2).build();

	std::println("string1: {}, s1: {} {}", string1, s1.str(), s1.capacity());
	std::println("string2: {}, s2: {} {}", string2, s2.str(), s2.capacity());

	return 0;
}
import std;

int sum_of_dig(int num)
{
	int sum = 0;
	sum += num / 100;
	sum += num % 100 / 10;
	sum += num % 10;
	return sum;
}

int prod_of_dig(int num)
{
	int prod = 1;
	prod *= num / 100;
	prod *= num % 100 / 10;
	prod *= num % 10;
	return prod;
}

void minutes_passed()
{
	std::println("Введите текущее время в секундах: ");
	int current_time = 0;
	std::cin >> current_time;
	int minutes = 0;
	minutes = current_time % 3600 / 60;
	std::println("С начала последнего часа прошло: {} минут", minutes);
}

int invert_digits(int n)
{
	int reversed = 0;
	while (n > 0)
	{
		reversed = reversed * 10 + n % 10;
		n /= 10;
	}
	return reversed;
}

int all_right_digit(int n, int d)
{
	n = n * 10 + d;
	return n;
}
bool is_prime(int n)
{
	if (n == 1 || n == 2)
		return true;
	int del = 3;
	if (n % 2 == 0)
		return false;
	else
	{
		while (del < n / 2)
		{
			if (n % del == 0)
			{
				return false;
			}
			del += 2;
		}
	}
	return true;
}

int fact(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * fact(n - 1);
}

int gcd(int a, int b)
{
	if (b <= 0)
		return a;
	else
	{
		return gcd(b, a % b);
	}
}
int main()
{
	int opt = 0;
	std::println("Выберите пункт меню: ");
	std::cin >> opt;
	switch (opt)
	{
	case 1:
	{
		int num = 0;
		std::println("Введите трёхначное число:");
		std::cin >> num;
		int sum = sum_of_dig(num);
		int prod = prod_of_dig(num);
		std::println("Сумма: {} \n Произведние: {}", sum, prod);
		break;
	}
	case 2:
	{
		minutes_passed();
		break;
	}
	case 3:
	{
		int number = 0;
		std::println("Введите число: ");
		std::cin >> number;
		std::println("Это число в перевернутом виде: {}", invert_digits(number));
		break;
	}
	case 4:
	{
		std::println("Введите натуральное число n:");
		int n = 0;
		while (n <= 0)
		{
			std::cin >> n;
		}

		std::println("Введите цифру d:");
		int d = 0;
		do
		{
			std::cin >> d;
		} while (d < 0 || d > 9);

		int result = all_right_digit(n, d);

		std::println("Число с циферкой на конце: {}", result);

		break;
	}
	case 5:
	{
		int number = 0;
		std::println("Введите число для проверки на простоту: ");
		std::cin >> number;
		if (is_prime(number) == true)
			std::println("Вашe число простое");
		else
			std::println("Ваше число не простое");
		break;
	}
	case 6:
	{
		int num = 0;
		std::println("Введите число для подсчёта факториала: ");
		std::cin >> num;

		int f = fact(num);
		std::println("Факториал: {}", f);
		break;
	}
	case 7:
	{
		int a = 0, b = 0;
		std::println("Введите значения a и b: ");
		std::cin >> a >> b;
		std::println("НОД: {}", gcd(a, b));
		break;
	}
	default:
	{
		break;
	}
	}
	return 0;
}
import std;

// 2. Инвертирование порядка цифр
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

void invert_digits_exapmle()
{
	std::println("2. Функция invert_digits: меняет порядок цифр на обратный.");
	unsigned int n = 0;
	std::print("Введите положительное целое число: ");
	if (!(std::cin >> n) || n == 0)
	{
		std::println("Ошибка ввода.");
		return;
	}

	std::println("Исходное: {}, Обратное: {}", n, invert_digits(n));
}

// 3. Добавление цифры d справа к числу n
int append_digit(int n, int d)
{
	return n * 10 + (d % 10);
}

void append_digit_exapmle()
{
	std::println("3. Функция append_digit: добавляет цифру d справа к n.");
	unsigned int n = 0, d = 0;
	std::print("Введите число n и цифру d (0-9): ");
	if (!(std::cin >> n >> d))
	{
		std::println("Ошибка ввода.");
		return;
	}

	std::println("n = {}, d = {}, Результат: {}", n, d, append_digit(n, d));
}

// 4. Проверка числа на простоту
bool is_prime(int n)
{
	if (n < 2)
	{
		return false;
	}

	if (n == 2 || n == 3)
	{
		return true;
	}

	if (n % 2 == 0 || n % 3 == 0)
	{
		return false;
	}

	// Перебор делителей вида 6k±1 до √n
	// https://ru.wikipedia.org/wiki/Перебор_делителей
	for (int i = 5; i * i <= n; i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return false;
		}
	}

	return true;
}

void is_prime_exapmle()
{
	std::println("4. Функция is_prime: проверка на простоту.");
	unsigned int n = 0;
	std::print("Введите натуральное число: ");
	if (!(std::cin >> n))
	{
		std::println("Ошибка ввода.");
		return;
	}

	std::println("Число {} {}", n, is_prime(n) ? "является простым." : "НЕ является простым.");
}

// 5. Рекурсивный факториал
[[nodiscard]] constexpr unsigned long long fact(unsigned int n)
{
	return (n <= 1) ? 1ULL : n * fact(n - 1);
}

void fact_exapmle()
{
	std::println("5. Рекурсивная функция fact: вычисление факториала.");
	unsigned int n = 0;
	std::print("Введите n (0-20, чтобы избежать переполнения): ");
	if (!(std::cin >> n) || n > 20)
	{
		std::println("Ошибка ввода или n > 20.");
		return;
	}

	std::println("{}! = {}", n, fact(n));
}

// 6. Рекурсивный НОД (алгоритм Евклида)
[[nodiscard]] constexpr unsigned int gcd(unsigned int a, unsigned int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

void gcd_exapmle()
{
	std::println("6. Рекурсивная функция gcd: НОД по алгоритму Евклида.");
	unsigned int a = 0, b = 0;
	std::print("Введите два положительных целых числа a и b: ");
	if (!(std::cin >> a >> b) || a == 0 || b == 0)
	{
		std::println("Ошибка ввода.");
		return;
	}

	std::println("НОД({}, {}) = {}", a, b, gcd(a, b));
}

// 7. Рекурсивная сумма цифр (без циклов)
[[nodiscard]] constexpr unsigned int digit_sum(unsigned int n)
{
	return (n < 10) ? n : (n % 10) + digit_sum(n / 10);
}

void digit_sum_exapmle()
{
	std::println("7. Рекурсивная функция digit_sum: сумма цифр без циклов.");
	unsigned int n = 0;
	std::print("Введите целое число: ");
	if (!(std::cin >> n))
	{
		std::println("Ошибка ввода.");
		return;
	}

	std::println("Сумма цифр числа {} равна {}", n, digit_sum(n));
}

int main()
{
	invert_digits_exapmle();
	std::println();

	append_digit_exapmle();
	std::println();

	is_prime_exapmle();
	std::println();

	fact_exapmle();
	std::println();

	gcd_exapmle();
	std::println();

	digit_sum_exapmle();

	return 0;
}
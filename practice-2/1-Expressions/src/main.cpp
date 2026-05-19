import std;

// 1. Дано трёхзначное число. Найти сумму и произведение его цифр.
void sum_and_product()
{
	int num = 0;

	std::print("Введи трёхзначное число: ");

	std::cin >> num;

	int hundreds = num / 100;
	int tens = (num / 10) % 10;
	int units = num % 10;

	int sum = hundreds + tens + units;
	int product = hundreds * tens * units;

	std::println("Число: {}", num);
	std::println("Сумма: {}", sum);
	std::println("Произведение: {}", product);
}

// 2. С начала суток прошло n секунд. Найти количество полных минут, прошедших
// с начала последнего часа.
void minutes_of_current_hour()
{
	int n = 0;

	std::print("Сколько прошло с начала суток: ");

	std::cin >> n;

	int seconds = n % 3600;
	int minutes = seconds / 60;

	std::println("Количество полных минут: {}", minutes);
}

// 3. Дано целое число n из диапазона 1—365, и целое число k из диапазона 1—7.
// Определить номер дня недели для n-го дня года, если известно, что в этом году
// 1 января было днём недели с номером k.
void day_of_week()
{
	int n = 0;
	int k = 0;

	std::print("Введите день: ");
	std::cin >> n;

	std::print("Введите день недели первого января): ");
	std::cin >> k;

	int dayOfWeek = (k - 1 + (n - 1)) % 7 + 1;

	std::println("Номер дня недели для n-го дня года {}: ", dayOfWeek);
}

// 4. Дано трехзначное число. Проверить истинность высказывания: “Цифры данного
// числа образуют возрастающую последовательность”.
void check_digits_order()
{
	int num = 0;

	std::print("Введи трёхзначное число: ");

	std::cin >> num;

	int hundreds = num / 100;
	int tens = (num / 10) % 10;
	int units = num % 10;

	if (hundreds < tens && tens < units)
	{
		std::println("Цифры данного числа образуют возрастающую последовательность");
	}
	else
	{
		std::println("Цифры данного числа НЕобразуют возрастающую последовательность");
	}
}

// 5
void rook_move()
{
	int x1, x2, y1, y2;
	std::println("введите клетку, на которой стоит ладья (x1,y1):");
	std::cin >> x1 >> y1;
	std::println("введите клетку, в которую перейдёт ладья (x2,y2):");
	std::cin >> x2 >> y2;
	bool result(x1 == x2 || y1 == y2);
	std::println("{}", result);
}

int main()
{
	sum_and_product();
	minutes_of_current_hour();
	day_of_week();
	check_digits_order();
	rook_move();

	return 0;
}
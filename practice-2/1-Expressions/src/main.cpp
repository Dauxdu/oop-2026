import std;

void sum_and_product()
{
	std::println("1. Дано трёхзначное число. Найти сумму и произведение его цифр.");

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

void minutes_of_current_hour()
{
	std::println("2. С начала суток прошло n секунд. Найти количество полных минут, прошедших с начала последнего часа.");

	int n = 0;

	std::print("Сколько прошло с начала суток: ");

	std::cin >> n;

	int seconds = n % 3600;
	int minutes = seconds / 60;

	std::println("Количество полных минут: {}", minutes);
}

void day_of_week()
{
	std::println("3. Дано целое число n из диапазона 1—365, и целое число k из диапазона 1—7. Определить номер дня недели для n-го дня года, если известно, что в этом году 1 января было днём недели с номером k.");

	int n = 0;
	int k = 0;

	std::print("Введите день: ");
	std::cin >> n;

	std::print("Введите день недели первого января): ");
	std::cin >> k;

	int dayOfWeek = (k - 1 + (n - 1)) % 7 + 1;

	std::println("Номер дня недели для n-го дня года {}: ", dayOfWeek);
}

void check_digits_order()
{
	std::println("4. Дано трёхзначное число. Проверить, образуют ли его цифры возрастающую последовательность (например, 123, 578).");

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

void rook_move()
{
	std::println("5. Даны координаты двух различных полей шахматной доски x1 , y1 , x2 , y2 (целые числа в диапазоне 1–8). Проверить истинность высказывания : “Ладья за один ход может перейти с одного поля на другое”.");

	int x1, y1, x2, y2;

	std::println("Введите клетку, на которой стоит ладья (x1 y1):");
	std::cin >> x1 >> y1;

	std::println("Введите клетку, в которую перейдёт ладья (x2 y2):");
	std::cin >> x2 >> y2;

	bool result = (x1 == x2 || y1 == y2);

	std::println("{}", result);
}

int main()
{
	sum_and_product();
	std::println();
	minutes_of_current_hour();
	std::println();
	day_of_week();
	std::println();
	check_digits_order();
	std::println();
	rook_move();

	return 0;
}
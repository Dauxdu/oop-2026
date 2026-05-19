import std;

int main()
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
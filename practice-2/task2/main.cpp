import std;

int main()
{
	int current_time = 0;
	std::println("Введите текущее время(в секундах)");
	std::cin >> current_time;
	int seconds = 0;
	seconds = current_time % 3600;
	std::println("С начала последнего часа прошло: {} секунд", seconds);
	return 0;
}
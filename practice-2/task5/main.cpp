import std;

int main()
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
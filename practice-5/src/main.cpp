import std;

class fraction
{
private:
	int _numerator = 0;
	int _denominator = 1;

	void normalize()
	{
		if (_denominator == 0)
		{
			_denominator = 1;
		}

		if (_denominator <= 0)
		{
			_denominator = std::abs(_denominator);
		}

		if (_numerator == 0)
		{
			_denominator = 1;
		}

		int gcd = std::gcd(_numerator, _denominator);
		_numerator /= gcd;
		_denominator /= gcd;
	}

public:
	fraction(int numerator)
	{
		_numerator = numerator;

		normalize();
	}

	fraction(int numerator, int denominator)
	{
		_numerator = numerator;
		_denominator = denominator;

		normalize();
	}

	int get_numerator() const
	{
		return _numerator;
	}

	int get_denominator() const
	{
		return _denominator;
	}

	fraction &operator+=(const fraction &fr)
	{
		_numerator = get_numerator() * fr.get_denominator() + fr.get_numerator() * get_denominator();
		_denominator = get_denominator() * fr.get_denominator();

		normalize();

		return *this;
	}

	fraction &operator-=(const fraction &fr)
	{
		_numerator = get_numerator() * fr.get_denominator() - fr.get_numerator() * get_denominator();
		_denominator = get_denominator() * fr.get_denominator();

		normalize();

		return *this;
	}

	fraction &operator++()
	{
		_numerator = get_numerator() + get_denominator();

		return *this;
	}

	fraction operator++(int)
	{
		fraction fr(*this);
		_numerator = get_numerator() + get_denominator();

		return fr;
	}

	fraction &operator*=(const fraction &fr)
	{
		_numerator = get_numerator() * fr.get_numerator();
		_denominator = get_denominator() * fr.get_denominator();

		normalize();

		return *this;
	}
};

fraction operator+(const fraction &fr_1, const fraction &fr_2)
{
	fraction fr(fr_1);
	return fr += fr_2;
}

fraction operator-(const fraction &fr_1, const fraction &fr_2)
{
	fraction fr(fr_1);
	return fr -= fr_2;
}

fraction operator*(const fraction &fr_1, const fraction &fr_2)
{
	fraction fr(fr_1);
	return fr *= fr_2;
}

std::ostream &operator<<(std::ostream &out, const fraction &fr)
{
	out << fr.get_numerator() << "/" << fr.get_denominator();
	return out;
}
std::string to_string(const fraction &fr)
{
	std::stringstream str;
	str << fr;
	return str.str();
}
bool to_file(const std::string &path, const fraction &fr)
{

	std::fstream str{path, str.out};
	if (!str.is_open())
	{
		return 1;
	}
	else
	{
		str << fr;
	}
	return 0;
}

int main()
{
	int n = 0;
	int d = 1;
	std::println("введите дробь 1: ");
	std::cin >> n >> d;
	fraction fr_1(n, d);
	std::println("введите дробь 2: ");
	std::cin >> n >> d;
	fraction fr_2(n, d);

	std::cout << "Первая дробь: " << fr_1 << std::endl;
	std::cout << "Вторая дробь: " << fr_2 << std::endl;

	std::println("Введите путь:");
	std::string path;
	std::cin >> path;
	to_file(path, fr_1);

	std::println("выберите действие (+, -, ++ или *): ");
	std::string op;
	std::cin >> op;
	if (op == "+")
	{
		fraction res = fr_1 + fr_2;
		std::println("{}+{}={}", to_string(fr_1), to_string(fr_2), to_string(res));
	}
	else if (op == "-")
	{
		fraction res = fr_1 - fr_2;
		std::println("{}-{}={}", to_string(fr_1), to_string(fr_2), to_string(res));
	}
	else if (op == "*")
	{
		fraction res = fr_1 * fr_2;
		std::println("{}*{}={}", to_string(fr_1), to_string(fr_2), to_string(res));
	}
	else if (op == "++")
	{
		fraction res_1 = fr_1;
		fraction res_2 = fr_2;
		std::println("{}++={}, ++{}={}", to_string(res_1), to_string(fr_1++), to_string(res_2), to_string(++fr_2));
	}

	return 0;
}
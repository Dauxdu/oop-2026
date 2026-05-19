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
};

fraction operator+(fraction fr_1, fraction fr_2)
{
	int sum_num = fr_1.get_numerator() * fr_2.get_denominator() + fr_2.get_numerator() * fr_1.get_denominator();
	int sum_denom = fr_1.get_denominator() * fr_2.get_denominator();

	fraction result(sum_num, sum_denom);
	return result;
}

fraction operator*(fraction fr_1, fraction fr_2)
{
	int mul_num = fr_1.get_numerator() * fr_2.get_numerator();
	int mul_denom = fr_1.get_denominator() * fr_2.get_denominator();

	fraction result(mul_num, mul_denom);
	return result;
}

std::string to_string(fraction fr)
{
	return std::format("{}/{}", fr.get_numerator(), fr.get_denominator());
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
	std::println("выберите действие (+ или *): ");
	std::string op;
	std::cin >> op;
	if (op == "+")
	{
		fraction res = fr_1 + fr_2;
		std::println("{}+{}={}", to_string(fr_1), to_string(fr_2), to_string(res));
	}
	else if (op == "*")
	{
		fraction res = fr_1 * fr_2;
		std::println("{}*{}={}", to_string(fr_1), to_string(fr_2), to_string(res));
	}

	return 0;
}
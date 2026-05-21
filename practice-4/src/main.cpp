import std;

class Fraction
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

		// I3
		if (_denominator < 0)
		{
			_denominator = std::abs(_denominator);
		}

		// I1
		if (_numerator == 0)
		{
			_denominator = 1;
			return;
		}

		// I2
		int gcd = std::gcd(_numerator, _denominator);
		_numerator /= gcd;
		_denominator /= gcd;
	}

public:
	// C1
	Fraction(int num) : _numerator(num)
	{
		normalize();
	}

	// C2
	Fraction(int num, int den) : _numerator(num), _denominator(den)
	{
		normalize();
	}

	int get_numerator() const noexcept
	{
		return _numerator;
	}

	int get_denominator() const noexcept
	{
		return _denominator;
	}
};

// F1
Fraction operator+(const Fraction &frac_1, const Fraction &frac_2)
{
	return {frac_1.get_numerator() * frac_2.get_denominator() + frac_2.get_numerator() * frac_1.get_denominator(),
			frac_1.get_denominator() * frac_2.get_denominator()};
}

// F1
Fraction operator-(const Fraction &frac_1, const Fraction &frac_2)
{
	return {frac_1.get_numerator() * frac_2.get_denominator() - frac_2.get_numerator() * frac_1.get_denominator(),
			frac_1.get_denominator() * frac_2.get_denominator()};
}

// F2
Fraction operator*(const Fraction &frac_1, const Fraction &frac_2)
{
	return {frac_1.get_numerator() * frac_2.get_numerator(),
			frac_1.get_denominator() * frac_2.get_denominator()};
}

// F3
std::string to_string(const Fraction &frac)
{
	return std::format("{}/{}", frac.get_numerator(), frac.get_denominator());
}

int main()
{
	std::println("Демонстрация работы с классом Fraction\n");

	int n1 = 0;
	int d1 = 0;
	int n2 = 0;
	int d2 = 0;
	std::print("Введите числитель и знаменатель первой дроби: ");
	std::cin >> n1 >> d1;
	Fraction f1{n1, d1};

	std::print("Введите числитель и знаменатель второй дроби: ");
	std::cin >> n2 >> d2;
	Fraction f2{n2, d2};

	std::println("\nПервая дробь : {}", to_string(f1));
	std::println("Вторая дробь: {}", to_string(f2));
	std::println("Сложение    : {}", to_string(f1 + f2));
	std::println("Вычитание   : {}", to_string(f1 - f2));
	std::println("Умножение   : {}", to_string(f1 * f2));

	return 0;
}
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

	// 1
	Fraction &operator+=(const Fraction &frac)
	{
		_numerator = _numerator * frac._denominator + frac._numerator * _denominator;
		_denominator = _denominator * frac._denominator;

		normalize();

		return *this;
	}

	// 1
	Fraction &operator-=(const Fraction &frac)
	{
		_numerator = _numerator * frac._denominator - frac._numerator * _denominator;
		_denominator = _denominator * frac._denominator;

		normalize();

		return *this;
	}

	// 1
	Fraction &operator*=(const Fraction &frac)
	{
		_numerator *= frac._numerator;
		_denominator *= frac._denominator;
		normalize();

		return *this;
	}

	// 3
	Fraction &operator++()
	{
		_numerator += _denominator;

		return *this;
	}

	// 3
	Fraction operator++(int)
	{
		Fraction frac = *this;
		++(*this);

		return frac;
	}
};

Fraction operator+(const Fraction &frac_1, const Fraction &frac_2)
{
	Fraction frac{frac_1};

	return frac += frac_2;
}

Fraction operator-(const Fraction &frac_1, const Fraction &frac_2)
{
	Fraction frac{frac_1};

	return frac -= frac_2;
}

Fraction operator*(const Fraction &frac_1, const Fraction &frac_2)
{
	Fraction frac{frac_1};

	return frac *= frac_2;
}

std::ostream &operator<<(std::ostream &out, const Fraction &frac)
{
	return out << frac.get_numerator() << "/" << frac.get_denominator();
}

std::string to_string(const Fraction &frac)
{
	std::stringstream str;
	str << frac;
	return str.str();
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

	std::println("\nБинарные операторы");
	std::println("	{} + {} = {}", to_string(f1), to_string(f2), to_string(f1 + f2));
	std::println("	{} - {} = {}", to_string(f1), to_string(f2), to_string(f1 - f2));
	std::println("	{} * {} = {}", to_string(f1), to_string(f2), to_string(f1 * f2));

	Fraction f3 = f1;
	std::println("\nОператоры +=, -=, *=");
	std::println("	f3 = {}", to_string(f3));
	f3 += f2;
	std::println("	f3 += f2 → {}", to_string(f3));
	f3 -= f2;
	std::println("	f3 -= f2 → {}", to_string(f3));
	f3 *= f2;
	std::println("	f3 *= f2 → {}", to_string(f3));

	std::println("\nПрефиксный и постфиксный ++");
	Fraction f4 = f1;
	std::println("	f4 = {}, ++f4 = {}, f4++ = {}", to_string(f4), to_string(++f4), to_string(f4++));
	std::println("	После операций: f4 = {}", to_string(f4));

	std::println("\nВывод через operator<<");
	std::stringstream str;
	str << f1 << " + " << f2 << " = " << (f1 + f2);
	std::println("	std::stringstream: {}", str.str());

	std::print("	std::cout: ");
	std::cout << f1 << '\n';

	std::println("	std::fstream: output.txt");
	if (std::fstream file("output.txt"); file)
	{
		file << "Запись в файл: " << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
	}

	return 0;
}
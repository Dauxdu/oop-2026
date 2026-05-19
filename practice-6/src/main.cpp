import std;

class String
{
private:
	char *_s = nullptr;
	int _size = 0;

	void str_copy(const char *s)
	{
		_size = std::strlen(s);
		_s = new char[_size + 1];
		std::strcpy(_s, s);
	}

public:
	String() {}

	String(const char *s)
	{
		str_copy(s);
	}

	~String()
	{
		delete[] _s;
		_s = nullptr;
		_size = 0;
	}

	String(const String &other)
	{
		str_copy(other._s);
	}

	String(String &&other)
	{
		_s = other._s;
		_size = other._size;

		other._s = nullptr;
		other._size = 0;
	}

	String &operator=(const String &other)
	{
		if (this != &other)
		{
			str_copy(other._s);
		}
		return *this;
	}

	String &operator=(String &&other)
	{
		if (this != &other)
		{
			_s = other._s;
			_size = other._size;

			other._s = nullptr;
			other._size = 0;
		}
		return *this;
	}

	char operator[](int const index)
	{
		return _s[index];
	}

	int size()
	{
		return _size;
	}

	const char *str()
	{
		return _s;
	}
};

namespace std
{
	template <>
	struct formatter<String, char>
	{
		constexpr auto parse(format_parse_context &ctx)
		{
			auto it = ctx.begin();
			while (it != ctx.end() && *it != '}')
			{
				++it;
			}
			return it;
		}

		auto format(String p, format_context &ctx) const
		{
			std::ostringstream oss;
			oss << p.str();
			const auto s = oss.str();
			return std::copy(s.begin(), s.end(), ctx.out());
		}
	};
}; // struct formatter

class StringBuilder
{
private:
	std::string _buffer;

public:
	StringBuilder() = default;

	void reserve(int bytes)
	{
		_buffer.reserve(bytes);
	}

	StringBuilder &append(const std::string &str)
	{
		_buffer.append(str);
		return *this;
	}

	StringBuilder &append(const int num)
	{
		_buffer.append(std::to_string(num));
		return *this;
	}

	StringBuilder &append(const float num)
	{
		_buffer.append(std::to_string(num));
		return *this;
	}

	std::string build() const &
	{
		return _buffer;
	}

	std::string build() &&
	{
		return std::move(_buffer);
	}

	std::size_t size() const
	{
		return _buffer.size();
	}

	std::size_t capacity() const
	{
		return _buffer.capacity();
	}

	std::string str() const
	{
		return _buffer;
	}
};

int main()
{
	char st[] = "привет, мир!";
	String str(st);
	std::println("{}", str);
	String str1(str);
	std::println(" str1: {}", str1);

	String str2 = str1;
	std::println("str2: {}", str2);

	String str3(std::move(str1));
	std::println("str3: {}", str3);
	String str4 = std::move(str2);
	std::println("str4: {}", str4);

	std::println("str1 new: {}", str1);
	std::println("str2 new: {}", str2);

	std::println("---------------------------------------------------");
	StringBuilder s1;
	int size;
	std::println("Введите объем памяти:");
	std::cin >> size;
	s1.reserve(size);

	int choice = 0;

	while (choice != 4)
	{
		std::println("Выберите дейтсвие:(1)Добавить строку, (2) Добавить int , (3) Добавить float, (4) Выход");
		std::cin >> choice;
		if (choice == 1)
		{
			std::println("Введите строку:");
			std::string s_1;
			std::cin >> s_1;
			s1.append(s_1);
		}

		else if (choice == 2)
		{
			std::println("Введите целочисленное значение:");
			int s_1;
			std::cin >> s_1;
			s1.append(s_1);
		}
		else if (choice == 3)
		{
			std::println("Введите float :");
			float s_1;
			std::cin >> s_1;
			s1.append(s_1);
		}
	}
	std::println("Емкость:{} Размер:{} Строка:{}", s1.capacity(), s1.size(), s1.str());

	StringBuilder s2;
	s2 = s1;
	std::println("s1: {}, s2: {}", s1.str(), s2.str());
	std::string string1 = s1.build();
	std::string string2 = std::move(s2).build();
	std::println("string1: {}, s1: {} {}", string1, s1.str(), s1.capacity());
	std::println("string2: {}, s2: {} {}", string2, s2.str(), s2.capacity());

	return 0;
}
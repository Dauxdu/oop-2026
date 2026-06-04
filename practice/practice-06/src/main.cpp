import std;

class String
{
private:
	char *_c = nullptr;
	std::size_t _size = 0;

	void allocate_memory(const char *c, std::size_t len)
	{
		_c = new char[len + 1];
		std::memcpy(_c, c, len + 1);
		_size = len;
	}

	void free_memory() noexcept
	{
		delete[] _c;
		_c = nullptr;
		_size = 0;
	}

public:
	String() = default;

	String(const char *str)
	{
		if (!str)
		{
			throw std::invalid_argument("Переданная строка ни на что не указывает");
		}

		allocate_memory(str, std::strlen(str));
	}

	~String()
	{
		free_memory();
	}

	String(const String &other)
	{
		if (other._c)
		{
			allocate_memory(other._c, other._size);
		}
	}

	String(String &&other) noexcept : _c(other._c), _size(other._size)
	{
		other._c = nullptr;
		other._size = 0;
	}

	String &operator=(const String &other)
	{
		if (this != &other)
		{
			free_memory();
			if (other._c)
			{
				allocate_memory(other._c, other._size);
			}
		}

		return *this;
	}

	String &operator=(String &&other) noexcept
	{
		if (this != &other)
		{
			free_memory();
			_c = other._c;
			_size = other._size;
			other._c = nullptr;
			other._size = 0;
		}

		return *this;
	}

	char operator[](std::size_t index) const
	{
		return _c[index];
	}

	char &operator[](std::size_t index)
	{
		return _c[index];
	}

	std::size_t size() const noexcept
	{
		return _size;
	}

	const char *get_c() const noexcept
	{
		return _c;
	}
};

template <>
struct std::formatter<String> : std::formatter<std::string_view>
{
	auto format(const String &s, auto &ctx) const
	{
		return std::formatter<std::string_view>::format(s.get_c(), ctx);
	}
};

class StringBuilder
{
private:
	std::string _buffer;

public:
	StringBuilder() = default;

	void reserve(std::size_t new_size)
	{
		_buffer.reserve(new_size);
	}

	StringBuilder &append(const std::string &str)
	{
		_buffer.append(str);

		return *this;
	}

	StringBuilder &append(int number)
	{
		_buffer.append(std::to_string(number));

		return *this;
	}

	StringBuilder &append(float number)
	{
		_buffer.append(std::to_string(number));

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
};

int main()
{
	std::println("\n--------------------------------");
	std::println("String Example");

	String s1("C++");
	s1[0] = 'A';
	std::println("	Замена первого символа на 'A': '{}'", s1);
	std::println("	Размер строки: {}", s1.size());

	String s2 = std::move(s1);
	std::println("	Перемещенный объект: '{}'", s2);
	std::println("	Первый объект пуст? {}", s1.size() == 0);
	std::println("--------------------------------\n");

	std::println("\n--------------------------------");
	std::println("StringBuilder Example");

	StringBuilder sb;
	sb.reserve(64);
	sb.append("Студент набрал ").append(95).append(" из ").append(100).append(" баллов");

	std::string result = sb.build();
	std::println("Lvalue build: '{}'", result);
	std::println("   Размер буфера после: {}", sb.build().size());

	std::string temp = StringBuilder().append("Temp  ").append(123).build();
	std::println("Rvalue build: '{}'", temp);
	std::println("--------------------------------\n");

	return 0;
}
import std;

class ICounter
{
public:
	virtual ~ICounter() = default;
	virtual int get_value() const = 0;
	virtual std::string get_type() const = 0;
	virtual bool is_limit_reached() const = 0;
	virtual void increment() = 0;
	virtual void reset() = 0;
};

class BoundedCounter final : public ICounter
{
private:
	int _limit = 0;
	int _counter = 0;

public:
	BoundedCounter(int limit) : _limit(limit) {}

	int get_value() const override
	{
		return _counter;
	}

	std::string get_type() const override
	{
		return "BoundedCounter: " + std::to_string(_limit);
	}

	bool is_limit_reached() const override
	{
		return _limit == _counter;
	}

	void increment() override
	{
		if (!is_limit_reached())
		{
			++_counter;
		}
	}

	void reset() override
	{
		_counter = 0;
	}
};

class CyclicCounter final : public ICounter
{
private:
	int _limit = 0;
	int _counter = 0;

public:
	CyclicCounter(int limit) : _limit(limit) {}

	int get_value() const override
	{
		return _counter;
	}

	std::string get_type() const override
	{
		return "CyclicCounter: " + std::to_string(_limit);
	}

	bool is_limit_reached() const override
	{
		return _counter >= _limit;
	}

	void reset() override
	{
		_counter = 0;
	}

	void increment() override
	{
		if (!is_limit_reached())
		{
			++_counter;
		}
		else
		{
			reset();
		}
	}
};

class StepCounter final : public ICounter
{
private:
	int _limit = 0;
	int _counter = 0;
	int _step = 0;

public:
	StepCounter(int limit, int step) : _limit(limit), _step(step) {}

	int get_value() const override
	{
		return _counter;
	}

	std::string get_type() const override
	{
		return "StepCounter: " + std::to_string(_limit);
	}

	bool is_limit_reached() const override
	{
		return _counter == _limit;
	}

	void reset() override
	{
		_counter = 0;
	}

	void increment() override
	{
		if ((_counter + _step) <= _limit)
		{
			_counter += _step;
		}
	}
};

void bounded_counter_example()
{
	std::println("\n--------------------------------");
	std::println("BoundedCounter Example");

	BoundedCounter counter(5);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing:");
	for (int i = 0; i < 7; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

void cyclic_counter_example()
{
	std::println("\n--------------------------------");
	std::println("CyclicCounter Example");

	CyclicCounter counter(4);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing (cyclic behavior):");
	for (int i = 0; i < 7; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

void step_counter_example()
{
	std::println("\n--------------------------------");
	std::println("StepCounter Example");

	StepCounter counter(9, 3);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing by step:");
	for (int i = 0; i < 5; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

int main()
{
	bounded_counter_example();
	cyclic_counter_example();
	step_counter_example();

	return 0;
}
import std;

class ICounter
{

protected:
	int _limit = 0;
	int _counter = 0;

public:
	virtual bool isLimitReached() const noexcept = 0;

	virtual void increment() noexcept = 0;

	virtual void reset() noexcept = 0;

	virtual int getValue() const noexcept = 0;

	virtual std::string getType() const noexcept = 0;

	virtual ~ICounter() = default;
};

class BoundedCounter final : public ICounter
{

public:
	BoundedCounter(int limit) noexcept
	{
		_limit = limit;
	}

	bool isLimitReached() const noexcept override
	{
		return _limit == _counter;
	}

	void increment() noexcept override
	{
		if (!isLimitReached())
		{
			++_counter;
		}
	}

	void reset() noexcept override
	{
		_counter = 0;
	}

	int getValue() const noexcept override
	{
		return _counter;
	}

	std::string getType() const noexcept override
	{
		return "BoundedCounter: " + std::to_string(_limit);
	}
};

class CyclicCounter final : public ICounter
{
public:
	CyclicCounter(int limit) noexcept
	{
		_limit = limit;
		_counter = 0;
	}

	bool isLimitReached() const noexcept override
	{
		return _counter >= _limit;
	}

	void reset() noexcept override
	{
		_counter = 0;
	}

	void increment() noexcept override
	{

		if (!isLimitReached())
		{
			++_counter;
			return;
		}

		reset();
	}

	int getValue() const noexcept override
	{
		return _counter;
	}

	std::string getType() const noexcept override
	{
		return "CyclicCounter: " + std::to_string(_limit);
	}
};

class StepCounter final : public ICounter
{

private:
	int _step = 0;

public:
	StepCounter(int limit, int step) noexcept
	{
		_limit = limit;
		_counter = 0;
		_step = step;
	}

	bool isLimitReached() const noexcept override
	{
		return _counter == _limit;
	}

	void reset() noexcept override
	{
		_counter = 0;
	}

	void increment() noexcept override
	{
		if ((_counter + _step) <= _limit)
		{
			_counter += _step;
		}
	}

	int getValue() const noexcept override
	{
		return _counter;
	}

	std::string getType() const noexcept override
	{
		return "StepCounter: " + std::to_string(_limit);
	}
};

int main()
{
	return 0;
}

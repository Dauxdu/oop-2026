export module collections:Stack;

import std;
import interface;

export template <typename T>
class StackEnumerator final : public IEnumerator<T>
{
private:
	std::stack<T> _stack;
	bool _is_first = true;

public:
	explicit StackEnumerator(std::stack<T> stack)
		: _stack(std::move(stack)) {}

	bool MoveNext() override
	{
		if (_is_first && _stack.size() > 0)
		{
			_is_first = false;
			return true;
		}

		if (_stack.size() > 1)
		{
			_stack.pop();
			return true;
		}
		return false;
	}

	const T &Current() const override
	{
		if (_stack.size() == 0)
		{
			throw std::logic_error("Stack is empty");
		}
		return _stack.top();
	}
};

export template <typename T>
class Stack : public IEnumerable<T>
{
private:
	std::stack<T> _stack;

public:
	int Count() const
	{

		return _stack.size();
	}
	void Push(T obj)
	{
		_stack.push(obj);
	}
	T Peek() const
	{
		return _stack.top();
	}
	T Pop()
	{
		if (_stack.empty())
		{
			throw std::logic_error("Stack is empty");
		}

		T last = _stack.top();
		_stack.pop();
		return last;
	}

	std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
	{
		return std::make_unique<StackEnumerator<T>>(_stack);
	}
};

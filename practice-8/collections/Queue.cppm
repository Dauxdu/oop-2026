export module collections:Queue;

import std;
import interface;

export template <typename T>
class QueueEnumerator final : public IEnumerator<T>
{
private:
	std::queue<T> _queue;
	bool _is_first = true;

public:
	explicit QueueEnumerator(std::queue<T> queue)
		: _queue(std::move(queue)) {}

	bool MoveNext() override
	{
		if (_is_first && _queue.size() > 0)
		{
			_is_first = false;
			return true;
		}

		if (_queue.size() > 0)
		{
			_queue.pop();
			return true;
		}
		return false;
	}

	const T &Current() const override
	{
		if (_queue.size() == 0)
		{
			throw std::logic_error("Queue is empty");
		}
		return _queue.front();
	}
};

export template <typename T>
class Queue : public IEnumerable<T>
{
	std::queue<T> _queue;

public:
	int Count() const
	{
		return _queue.size();
	}

	void Enqueue(T item)
	{
		_queue.push(item);
	}

	T Peek() const
	{
		return _queue.front();
	}

	T Dequeue()
	{
		if (_queue.empty())
		{
			throw std::logic_error("Queue is empty");
		}

		T last = _queue.front();
		_queue.pop();
		return last;
	}

	std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
	{
		return std::make_unique<QueueEnumerator<T>>(_queue);
	}
};

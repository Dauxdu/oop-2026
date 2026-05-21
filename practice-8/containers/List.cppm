export module containers:List;

import std;
import interfaces;
import enumerators;

export template <typename TValue>
class List final : public ICollection<TValue>
{
private:
	std::vector<TValue> _list;

public:
	std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
	{
		return std::make_unique<ListEnumerator<TValue>>(_list);
	}

	void Add(const TValue &item) override
	{
		_list.push_back(item);
	}

	bool Remove(const TValue &item) override
	{
		return std::erase(_list, item) > 0;
	}

	void Clear() override
	{
		_list.clear();
	}

	std::size_t Count() const override
	{
		return _list.size();
	}

	bool Contains(const TValue &item) const override
	{
		return std::find(_list.begin(), _list.end(), item) != _list.end();
	}

	std::size_t Capacity() const
	{
		return _list.capacity();
	}

	void SetCapacity(std::size_t capacity)
	{
		_list.reserve(capacity);
	}

	void Insert(std::size_t index, const TValue &item)
	{
		if (index > _list.size())
		{
			throw std::out_of_range("List::Insert: index out of range");
		}

		_list.insert(_list.begin() + index, item);
	}

	void RemoveAt(std::size_t index)
	{
		if (index >= _list.size())
		{
			throw std::out_of_range("List::RemoveAt: index out of range");
		}

		_list.erase(_list.begin() + index);
	}

	TValue &operator[](std::size_t index)
	{
		if (index >= _list.size())
		{
			throw std::out_of_range("List::operator[]: index out of range");
		}

		return _list[index];
	}

	const TValue &operator[](std::size_t index) const
	{
		if (index >= _list.size())
		{
			throw std::out_of_range("List::operator[]: index out of range");
		}

		return _list[index];
	}
};
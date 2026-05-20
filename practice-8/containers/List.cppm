export module containers:List;

import std;
import interfaces;
import enumerators;

export template <typename T>
class List final : public ICollection<T>
{
private:
	std::vector<T> _list;

public:
	std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
	{
		return std::make_unique<ListEnumerator<T>>(_list);
	}

	std::size_t Count() const override
	{
		return _list.size();
	}

	void Add(const T &item) override
	{
		_list.push_back(item);
	}

	[[nodiscard]] bool Remove(const T &item) override
	{
		return std::erase(_list, item) > 0;
	}

	void Clear() override
	{
		_list.clear();
	}

	bool Contains(const T &item) const override
	{
		return std::find(_list.begin(), _list.end(), item) != _list.end();
	}

	[[nodiscard]] std::size_t Capacity() const
	{
		return _list.capacity();
	}

	void SetCapacity(std::size_t capacity)
	{
		_list.reserve(capacity);
	}

	[[nodiscard]] T &operator[](std::size_t index)
	{
		if (index >= _list.size())
		{
			throw std::out_of_range("List::operator[]: index out of range");
		}
		return _list[index];
	}

	[[nodiscard]] const T &operator[](std::size_t index) const
	{
		if (index >= _list.size())
		{
			throw std::out_of_range("List::operator[]: index out of range");
		}
		return _list[index];
	}

	void Insert(std::size_t index, const T &item)
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
};
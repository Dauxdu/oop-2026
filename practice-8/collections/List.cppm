export module collections:List;

import std;
import interface;

export template <typename T>
class ListEnumerator : public IEnumerator<T>
{
	std::vector<T> &_v;
	int _index = -1;

public:
	ListEnumerator(std::vector<T> &v) : _v(v) {}
	bool MoveNext() override
	{
		if (_index < _v.size() - 1)
		{
			++_index;
			return true;
		}
		return false;
	}

	const T &Current() const override
	{
		return _v[_index];
	}
};

export template <typename T>
class List : public ICollection<T>
{
private:
	std::vector<T> _list;

public:
	List() = default;

	std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
	{
		return std::unique_ptr<ListEnumerator<T>>(new ListEnumerator<T>(_list));
	}

	int Count() const override
	{
		return _list.size();
	}
	void Add(T item) override
	{
		_list.push_back(item);
	}
	void Clear() override
	{
		_list.clear();
	}
	bool Contains(T item) const override
	{
		return std::find(_list.begin(), _list.end(), item) != _list.end();
	}
	bool Remove(T item) override
	{
		auto iter = std::find(_list.begin(), _list.end(), item);
		if (iter != _list.end())
		{
			_list.erase(iter);
			return true;
		}
		return false;
	}

	int Capacity() const
	{
		return _list.capacity();
	}

	void SetCapacity(int capacity)
	{
		_list.reserve(capacity);
	}

	T operator[](int index) const
	{
		if (index > _list.size() - 1 || index < 0)
		{
			throw std::out_of_range("Invalid index");
		}
		return _list[index];
	}

	T &operator[](int index)
	{
		if (index > _list.size() - 1 || index < 0)
		{
			throw std::out_of_range("Invalid index");
		}
		return _list[index];
	}

	void Insert(int index, T item)
	{
		_list.insert(_list.begin() + index, item);
	}

	void RemoveAt(int index)
	{
		_list.erase(_list.begin() + index);
	}
};

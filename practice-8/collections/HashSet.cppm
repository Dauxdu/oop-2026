export module collections:HashSet;

import std;
import interface;

export template <typename T>
class HashSetEnumerator : public IEnumerator<T>
{
	typename std::unordered_set<T>::iterator _iter;
	typename std::unordered_set<T>::iterator _end;
	bool _is_first = true;

public:
	HashSetEnumerator(std::unordered_set<T> &hash_set) : _iter(hash_set.begin()), _end(hash_set.end()) {}

	bool MoveNext() override
	{
		if (_is_first && _iter != _end)
		{
			_is_first = false;
			return true;
		}

		if (_iter != _end)
		{
			_iter++;
			return true;
		}
		return false;
	}

	const T &Current() const
	{
		if (_iter == _end)
		{
			throw std::out_of_range("Выход за пределы");
		}
		return *_iter;
	}
};

export template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
class HashSet : public ICollection<T>
{
	std::unordered_set<T, Hash, KeyEqual> _set;

public:
	int Count() const override
	{
		return _set.size();
	}

	void Add(T item) override
	{
		_set.insert(item);
	}

	void Clear() override
	{
		_set.clear();
	}

	bool Contains(T item) const override
	{
		return _set.contains(item);
	}

	bool Remove(T item) override
	{
		if (Contains(item))
		{
			_set.erase(item);
			return true;
		}
		return false;
	}

	int Capacity() const
	{
		return _set.bucket_count();
	}

	void SetCapacity(int capacity)
	{
		_set.reserve(capacity);
	}

	std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
	{
		return std::make_unique<HashSetEnumerator<T>>(_set);
	}
};

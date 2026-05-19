export module collections:Dictionary;

import std;
import interface;

export template <typename TKey, typename TValue>
class DictionaryEnumerator : public IEnumerator<std::pair<const TKey, TValue>>
{
	typename std::unordered_map<TKey, TValue>::iterator _iter;
	typename std::unordered_map<TKey, TValue>::iterator _end;
	bool _is_first = true;

public:
	DictionaryEnumerator(std::unordered_map<TKey, TValue> &dictionary) : _iter(dictionary.begin()), _end(dictionary.end()) {}

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

	const std::pair<const TKey, TValue> &Current() const
	{
		if (_iter == _end)
		{
			throw std::out_of_range("Выход за пределы");
		}
		return *_iter;
	}
};

export template <typename TKey,
				 typename TValue,
				 typename Hash = std::hash<TKey>,
				 typename KeyEqual = std::equal_to<TKey>>
class Dictionary final : public ICollection<std::pair<const TKey, TValue>>
{
private:
	std::unordered_map<TKey, TValue, Hash, KeyEqual> _map;

public:
	int Count() const override
	{
		return _map.size();
	}

	void Add(std::pair<const TKey, TValue> pair) override
	{
		_map.insert(pair);
	}

	void Clear() override
	{
		_map.clear();
	}

	bool Contains(TKey key) const override
	{
		return _map.contains(key);
	}

	bool Remove(TKey key) override
	{
		if (Contains(key))
		{
			_map.erase(key);
			return true;
		}
		return false;
	}

	int Capacity() const
	{
		return _map.bucket_count();
	}

	void SetCapacity(int capacity)
	{
		_map.reserve(capacity);
	}

	TValue operator[](TKey key) const
	{
		if (!Contains(key))
		{
			throw std::out_of_range("Invalid key");
		}
		return _map[key];
	}

	TValue &operator[](TKey key)
	{
		if (!Contains(key))
		{
			throw std::out_of_range("Invalid key");
		}

		return _map[key];
	}

	std::unique_ptr<IEnumerator<std::pair<const TKey, TValue>>> GetEnumerator() const override
	{

		return std::make_unique<DictionaryEnumerator<TKey, TValue>>(_map);
	}
};

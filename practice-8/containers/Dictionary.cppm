export module containers:Dictionary;

import std;
import interfaces;

export template <typename TKey, typename TValue, typename THash = std::hash<TKey>, typename TEqual = std::equal_to<TKey>>
class DictionaryEnumerator final : public IEnumerator<std::pair<const TKey, TValue>>
{
private:
    bool _started = false;
    typename std::unordered_map<TKey, TValue, THash, TEqual>::const_iterator _iter;
    typename std::unordered_map<TKey, TValue, THash, TEqual>::const_iterator _end;

public:
    explicit DictionaryEnumerator(const std::unordered_map<TKey, TValue, THash, TEqual> &dictionary) : _started(false), _iter(dictionary.begin()), _end(dictionary.end()) {}

    bool MoveNext() override
    {
        if (!_started)
        {
            _started = true;
            return _iter != _end;
        }
        ++_iter;

        return _iter != _end;
    }

    const std::pair<const TKey, TValue> &Current() const override
    {
        if (!_started || _iter == _end)
        {
            throw std::logic_error("DictionaryEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};

export template <typename TKey, typename TValue, typename THash = std::hash<TKey>, typename TEqual = std::equal_to<TKey>>
class Dictionary final : public ICollection<std::pair<const TKey, TValue>>
{
private:
    std::unordered_map<TKey, TValue, THash, TEqual> _dictionary;

public:
    std::unique_ptr<IEnumerator<std::pair<const TKey, TValue>>> GetEnumerator() const override
    {
        return std::make_unique<DictionaryEnumerator<TKey, TValue, THash, TEqual>>(_dictionary);
    }

    void Add(const std::pair<const TKey, TValue> &item) override
    {
        auto [it, inserted] = _dictionary.insert(item);
        if (!inserted)
        {
            return;
        }
    }

    bool Remove(const std::pair<const TKey, TValue> &item) override
    {
        return _dictionary.erase(item.first) > 0;
    }

    void Clear() override
    {
        _dictionary.clear();
    }

    std::size_t Count() const override
    {
        return _dictionary.size();
    }

    bool Contains(const std::pair<const TKey, TValue> &item) const override
    {
        return _dictionary.contains(item.first);
    }

    std::size_t Capacity() const noexcept
    {
        return _dictionary.bucket_count();
    }

    void SetCapacity(const std::size_t capacity)
    {
        _dictionary.reserve(capacity);
    }

    const TValue &operator[](const TKey &key) const
    {
        auto it = _dictionary.find(key);
        if (it == _dictionary.end())
        {
            throw std::out_of_range("Dictionary::operator[]: Invalid key");
        }

        return it->second;
    }

    TValue &operator[](const TKey &key)
    {
        auto it = _dictionary.find(key);
        if (it == _dictionary.end())
        {
            throw std::out_of_range("Dictionary::operator[]: Invalid key");
        }

        return it->second;
    }
};
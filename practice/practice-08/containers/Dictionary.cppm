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
    DictionaryEnumerator(const std::unordered_map<TKey, TValue, THash, TEqual> &dictionary) : _iter(dictionary.begin()), _end(dictionary.end()) {}

    bool MoveNext() override
    {
        if (_started && _iter != _end)
        {
            ++_iter;
        }
        _started = true;

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
        _dictionary.insert(item);
    }

    bool Remove(const std::pair<const TKey, TValue> &item) override { return _dictionary.erase(item.first) > 0; }

    void Clear() override
    {
        _dictionary.clear();
    }

    std::size_t Count() const override { return _dictionary.size(); }

    bool Contains(const std::pair<const TKey, TValue> &item) const override { return _dictionary.contains(item.first); }

    std::size_t Capacity() const { return _dictionary.bucket_count(); }

    void SetCapacity(const std::size_t capacity) { _dictionary.reserve(capacity); }

    const TValue &operator[](const TKey &key) const { return _dictionary.at(key); }

    TValue &operator[](const TKey &key) { return _dictionary.at(key); }
};
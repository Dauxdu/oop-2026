export module containers:HashSet;

import std;
import interfaces;

export template <typename TValue, typename THash, typename TEqual>
class HashSetEnumerator final : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::unordered_set<TValue, THash, TEqual>::const_iterator _iter;
    typename std::unordered_set<TValue, THash, TEqual>::const_iterator _end;

public:
    explicit HashSetEnumerator(const std::unordered_set<TValue, THash, TEqual> &set) : _started(false), _iter(set.begin()), _end(set.end()) {}

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

    const TValue &Current() const override
    {
        if (!_started || _iter == _end)
        {
            throw std::logic_error("HashSetEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};

export template <typename TValue, typename THash = std::hash<TValue>, typename TEqual = std::equal_to<TValue>>
class HashSet final : public ICollection<TValue>
{
private:
    std::unordered_set<TValue, THash, TEqual> _set;

public:
    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<HashSetEnumerator<TValue, THash, TEqual>>(_set);
    }

    void Add(const TValue &item) override
    {
        _set.insert(item);
    }

    bool Remove(const TValue &item) override
    {
        return _set.erase(item) > 0;
    }

    void Clear() override
    {
        _set.clear();
    }

    std::size_t Count() const override
    {
        return _set.size();
    }

    bool Contains(const TValue &item) const override
    {
        return _set.find(item) != _set.end();
    }

    std::size_t Capacity() const
    {
        return _set.bucket_count();
    }

    void SetCapacity(std::size_t capacity)
    {
        _set.reserve(capacity);
    }
};
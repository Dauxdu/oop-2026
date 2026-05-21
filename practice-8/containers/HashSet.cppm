export module containers:HashSet;

import std;
import interfaces;
import enumerators;

export template <typename TValue, typename THash = std::hash<TValue>, typename TValueEqual = std::equal_to<TValue>>
class HashSet final : public ICollection<TValue>
{
private:
    std::unordered_set<TValue, THash, TValueEqual> _set;

public:
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

    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<HashSetEnumerator<TValue, THash, TValueEqual>>(_set);
    }
};
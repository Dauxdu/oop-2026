export module containers:HashSet;

import std;
import interfaces;

export template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
class HashSet final : public ICollection<T>
{
private:
    std::unordered_set<T, Hash, KeyEqual> _set;

public:
    std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
    {
        return std::make_unique<HashSetEnumerator<T>>(_set);
    }

    void Add(const T &item) override
    {
        _set.insert(item);
    }

    bool Remove(const T &item) override
    {
        return _set.erase(item) > 0;
    }

    void Clear() override
    {
        _set.clear();
    }

    [[nodiscard]] std::size_t Count() const override
    {
        return _set.size();
    }

    bool Contains(const T &item) const override
    {
        return _set.find(item) != _set.end();
    }

    [[nodiscard]] std::size_t Capacity() const
    {
        return _set.bucket_count();
    }

    void SetCapacity(std::size_t capacity)
    {
        _set.reserve(capacity);
    }
};
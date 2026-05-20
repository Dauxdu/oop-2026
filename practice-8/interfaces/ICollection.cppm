export module interfaces:ICollection;

import std;
import :IEnumerable;

export template <typename TValue>
class ICollection : public IEnumerable<TValue>
{
public:
    virtual ~ICollection() = default;
    virtual void Add(const TValue &item) = 0;
    virtual bool Remove(const TValue &item) = 0;
    virtual void Clear() = 0;
    virtual std::size_t Count() const = 0;
    virtual bool Contains(const TValue &item) const = 0;
};
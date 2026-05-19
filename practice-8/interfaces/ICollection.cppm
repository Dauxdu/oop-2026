export module interface:ICollection;

import :IEnumerable;

export template <typename T>
class ICollection : public IEnumerable<T>
{
public:
	virtual int Count() const = 0;
	virtual void Add(T item) = 0;
	virtual void Clear() = 0;
	virtual bool Contains(T item) const = 0;
	virtual bool Remove(T item) = 0;
	virtual ~ICollection() = default;
};

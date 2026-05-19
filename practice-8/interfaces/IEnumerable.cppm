export module interface:IEnumerable;

import std;
import :IEnumerator;

export template <typename T>
class IEnumerable
{
public:
	virtual std::unique_ptr<IEnumerator<T>> GetEnumerator() const = 0;
	virtual ~IEnumerable() = default;
};

export module interfaces:IEnumerable;

import std;
import :IEnumerator;

export template <typename TValue>
class IEnumerable
{
public:
    virtual ~IEnumerable() = default;
    virtual std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const = 0;
};
export module interfaces:IEnumerator;

export template <typename TValue>
class IEnumerator
{
public:
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual const TValue &Current() const = 0;
};
export module interfaces:IEnumerator;

export template <typename T>
class IEnumerator
{
public:
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual const T &Current() const = 0;
};
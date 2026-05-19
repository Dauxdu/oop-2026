export module interface:IEnumerator;

export template <typename T>
class IEnumerator
{
public:
	virtual bool MoveNext() = 0;
	virtual const T &Current() const = 0;
	virtual ~IEnumerator() = default;
};

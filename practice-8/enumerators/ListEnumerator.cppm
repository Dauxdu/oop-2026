export module enumerators:ListEnumerator;

import std;
import interfaces;

export template <typename TValue>
class ListEnumerator final : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::vector<TValue>::const_iterator _iter;
    typename std::vector<TValue>::const_iterator _end;

public:
    ListEnumerator(const std::vector<TValue> &vector)
        : _started(false), _iter(vector.begin()), _end(vector.end()) {}

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
            throw std::logic_error("ListEnumerator::Current: Invalid iterator");
        }
        return *_iter;
    }
};
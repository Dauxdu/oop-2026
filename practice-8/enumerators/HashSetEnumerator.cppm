export module enumerators:HashSetEnumerator;

import std;
import interfaces;

export template <typename TValue, typename THash, typename TValueEqual>
class HashSetEnumerator final : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::unordered_set<TValue, THash, TValueEqual>::const_iterator _iter;
    typename std::unordered_set<TValue, THash, TValueEqual>::const_iterator _end;

public:
    explicit HashSetEnumerator(const std::unordered_set<TValue, THash, TValueEqual> &set)
        : _started(false), _iter(set.begin()), _end(set.end()) {}

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
            throw std::logic_error("Invalid iterator");
        }
        return *_iter;
    }
};
export module enumerators:HashSetEnumerator;

import std;
import interfaces;

export template <typename TValue, typename THash, typename TEqual>
class HashSetEnumerator final : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::unordered_set<TValue, THash, TEqual>::const_iterator _iter;
    typename std::unordered_set<TValue, THash, TEqual>::const_iterator _end;

public:
    explicit HashSetEnumerator(const std::unordered_set<TValue, THash, TEqual> &set)
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
            throw std::logic_error("HashSetEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};
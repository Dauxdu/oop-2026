export module enumerators:DictionaryEnumerator;

import std;
import interfaces;

export template <typename TKey, typename TValue, typename THash = std::hash<TKey>, typename TEqual = std::equal_to<TKey>>
class DictionaryEnumerator final : public IEnumerator<std::pair<const TKey, TValue>>
{
private:
    bool _started = false;
    typename std::unordered_map<TKey, TValue, THash, TEqual>::const_iterator _iter;
    typename std::unordered_map<TKey, TValue, THash, TEqual>::const_iterator _end;

public:
    explicit DictionaryEnumerator(const std::unordered_map<TKey, TValue, THash, TEqual> &dictionary)
        : _started(false), _iter(dictionary.begin()), _end(dictionary.end()) {}

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

    const std::pair<const TKey, TValue> &Current() const override
    {
        if (!_started || _iter == _end)
        {
            throw std::logic_error("DictionaryEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};
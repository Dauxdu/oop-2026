export module enumerators:StackEnumerator;

import std;
import interfaces;

export template <typename TValue>
class StackEnumerator : public IEnumerator<TValue>
{
private:
    std::stack<TValue> _stack;
    bool _started = false;

public:
    explicit StackEnumerator(const std::stack<TValue> &stack) : _stack(stack) {}

    bool MoveNext() override
    {
        if (!_started)
        {
            _started = true;
            return !_stack.empty();
        }

        _stack.pop();

        return !_stack.empty();
    }

    const TValue &Current() const override
    {
        if (_stack.empty())
        {
            throw std::logic_error("StackEnumerator::Current: Invalid iterator");
        }

        return _stack.top();
    }
};
export module enumerators:StackEnumerator;

import std;
import interfaces;

export template <typename T>
class StackEnumerator : public IEnumerator<T>
{
private:
    std::stack<T> _stack;
    bool _started = false;

public:
    explicit StackEnumerator(const std::stack<T> &stack) : _stack(stack) {}

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

    const T &Current() const override
    {
        if (_stack.empty())
        {
            throw std::logic_error("Current() called before MoveNext() or after enumeration ended");
        }

        return _stack.top();
    }
};
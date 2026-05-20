export module enumerators:StackEnumerator;

import std;
import interfaces;

export template <typename T>
class StackEnumerator : public IEnumerator<T>
{
private:
    std::stack<T> _stack;
    bool _is_first = true;

public:
    explicit StackEnumerator(const std::stack<T> &stack) : _stack(stack) {}

    bool MoveNext() override
    {
        if (_is_first)
        {
            _is_first = false;
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
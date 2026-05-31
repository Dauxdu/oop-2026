export module containers:Stack;

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

export template <typename TValue>
class Stack : public IEnumerable<TValue>
{
private:
    std::stack<TValue> _stack;

public:
    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<StackEnumerator<TValue>>(_stack);
    }

    void Push(TValue item)
    {
        _stack.push(item);
    }

    TValue Pop()
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Pop: empty stack");
        }

        TValue item = std::move(_stack.top());
        _stack.pop();

        return item;
    }

    const TValue &Peek() const
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Peek: empty stack");
        }

        return _stack.top();
    }

    std::size_t Count() const
    {
        return _stack.size();
    }
};

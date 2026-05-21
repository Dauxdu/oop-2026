export module containers:Stack;

import std;
import interfaces;
import enumerators;

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

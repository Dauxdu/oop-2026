export module containers:Stack;

import std;
import interfaces;
import enumerators;

export template <typename T>
class Stack : public IEnumerable<T>
{
private:
    std::stack<T> _stack;

public:
    [[nodiscard]] std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
    {
        return std::make_unique<StackEnumerator<T>>(_stack);
    }

    [[nodiscard]] std::size_t Count() const
    {
        return _stack.size();
    }

    void Push(T item)
    {
        _stack.push(item);
    }

    [[nodiscard]] T Pop()
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Pop: empty stack");
        }

        T item = std::move(_stack.top());
        _stack.pop();

        return item;
    }

    [[nodiscard]] const T &Peek() const
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Peek: empty stack");
        }

        return _stack.top();
    }
};

export module containers:Stack;

import std;
import interfaces;

export template <typename TValue>
class StackEnumerator : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::vector<TValue>::const_iterator _iter;
    typename std::vector<TValue>::const_iterator _end;

public:
    StackEnumerator(const std::vector<TValue> &stack) : _iter(stack.begin()), _end(stack.end()) {}

    bool MoveNext() override
    {
        if (_started && _iter != _end)
        {
            ++_iter;
        }
        _started = true;

        return _iter != _end;
    }

    const TValue &Current() const override
    {
        if (!_started || _iter == _end)
        {
            throw std::logic_error("StackEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};

export template <typename TValue>
class Stack : public IEnumerable<TValue>
{
private:
    std::vector<TValue> _stack;

public:
    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<StackEnumerator<TValue>>(_stack);
    }

    void Push(TValue item)
    {
        _stack.push_back(std::move(item));
    }

    TValue Pop()
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Pop: empty stack");
        }

        TValue item = std::move(_stack.back());
        _stack.pop_back();

        return item;
    }

    const TValue &Peek() const
    {
        if (_stack.empty())
        {
            throw std::out_of_range("Stack::Peek: empty stack");
        }

        return _stack.back();
    }

    std::size_t Count() const
    {
        return _stack.size();
    }
};

export module containers:Queue;

import std;
import interfaces;

export template <typename TValue>
class QueueEnumerator final : public IEnumerator<TValue>
{
private:
    bool _started = false;
    typename std::deque<TValue>::const_iterator _iter;
    typename std::deque<TValue>::const_iterator _end;

public:
    QueueEnumerator(const std::deque<TValue> &queue) : _iter(queue.begin()), _end(queue.end()) {}

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
            throw std::logic_error("QueueEnumerator::Current: Invalid iterator");
        }

        return *_iter;
    }
};

export template <typename TValue>
class Queue : public IEnumerable<TValue>
{
private:
    std::deque<TValue> _queue;

public:
    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<QueueEnumerator<TValue>>(_queue);
    }

    void Enqueue(TValue item)
    {
        _queue.push_back(std::move(item));
    }

    TValue Dequeue()
    {
        if (_queue.empty())
        {
            throw std::out_of_range("Queue::Dequeue: empty queue");
        }

        TValue item = std::move(_queue.front());
        _queue.pop_front();

        return item;
    }

    const TValue &Peek() const
    {
        if (_queue.empty())
        {
            throw std::out_of_range("Queue::Peek: empty queue");
        }
        return _queue.front();
    }

    std::size_t Count() const { return _queue.size(); }
};
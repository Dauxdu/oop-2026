export module containers:Queue;

import std;
import interfaces;
import enumerators;

export template <typename TValue>
class Queue : public IEnumerable<TValue>
{
private:
    std::queue<TValue> _queue;

public:
    std::unique_ptr<IEnumerator<TValue>> GetEnumerator() const override
    {
        return std::make_unique<QueueEnumerator<TValue>>(_queue);
    }

    void Enqueue(TValue item)
    {
        _queue.push(item);
    }

    TValue Dequeue()
    {
        if (_queue.empty())
        {
            throw std::out_of_range("Queue::Dequeue: empty queue");
        }

        TValue item = std::move(_queue.front());
        _queue.pop();

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

    std::size_t Count() const
    {
        return _queue.size();
    }
};
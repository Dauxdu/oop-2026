export module containers:Queue;

import std;
import interfaces;
import enumerators;

export template <typename T>
class Queue : public IEnumerable<T>
{
private:
    std::queue<T> _queue;

public:
    [[nodiscard]] std::unique_ptr<IEnumerator<T>> GetEnumerator() const override
    {
        return std::make_unique<QueueEnumerator<T>>(_queue);
    }

    [[nodiscard]] std::size_t Count() const
    {
        return _queue.size();
    }

    void Enqueue(T item)
    {
        _queue.push(item);
    }

    [[nodiscard]] T Dequeue()
    {
        if (_queue.empty())
        {
            throw std::out_of_range("Queue::Dequeue: empty queue");
        }

        T item = std::move(_queue.front());
        _queue.pop();

        return item;
    }

    [[nodiscard]] const T &Peek() const
    {
        if (_queue.empty())
        {
            throw std::out_of_range("Queue::Peek: empty queue");
        }

        return _queue.front();
    }
};
export module enumerators:QueueEnumerator;

import std;
import interfaces;

export template <typename TValue>
class QueueEnumerator final : public IEnumerator<TValue>
{
private:
    std::queue<TValue> _queue;
    bool _is_first = true;

public:
    explicit QueueEnumerator(std::queue<TValue> queue) : _queue(std::move(queue)) {}

    bool MoveNext() override
    {

        if (_is_first)
        {
            _is_first = false;
            return !_queue.empty();
        }

        _queue.pop();

        return !_queue.empty();
    }

    const TValue &Current() const override
    {
        if (_queue.empty())
        {
            throw std::logic_error("Queue is empty");
        }

        return _queue.front();
    }
};
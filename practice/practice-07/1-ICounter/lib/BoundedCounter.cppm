export module counters:BoundedCounter;

import std;
import :ICounter;

export class BoundedCounter final : public ICounter
{
private:
    int _limit = 0;
    int _counter = 0;

public:
    BoundedCounter(int limit) : _limit(limit) {}

    int get_value() const override { return _counter; }

    std::string get_type() const override { return std::format("BoundedCounter: {}", _limit); }

    bool is_limit_reached() const override { return _counter >= _limit; }

    void increment() override
    {
        if (!is_limit_reached())
        {
            ++_counter;
        }
    }

    void reset() override
    {
        _counter = 0;
    }
};

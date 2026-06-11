export module counters:CyclicCounter;

import std;
import :ICounter;

export class CyclicCounter final : public ICounter
{
private:
    int _limit = 0;
    int _counter = 0;

public:
    CyclicCounter(int limit) : _limit(limit) {}

    int get_value() const override { return _counter; }

    std::string get_type() const override { return std::format("CyclicCounter: {}", _limit); }

    bool is_limit_reached() const override { return _counter == _limit - 1; }

    void increment() override
    {
        if (!is_limit_reached())
        {
            ++_counter;
        }
        else
        {
            reset();
        }
    }

    void reset() override
    {
        _counter = 0;
    }
};

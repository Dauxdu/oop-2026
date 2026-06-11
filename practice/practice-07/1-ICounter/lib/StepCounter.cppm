export module counters:StepCounter;

import std;
import :ICounter;

export class StepCounter final : public ICounter
{
private:
    int _limit = 0;
    int _counter = 0;
    int _step = 0;

public:
    StepCounter(int limit, int step) : _limit(limit), _step(step) {}

    int get_value() const override { return _counter; }

    std::string get_type() const override { return std::format("StepCounter: {} (step {})", _limit, _step); }

    bool is_limit_reached() const override { return (_counter + _step) > _limit; }

    void increment() override
    {
        if (!is_limit_reached())
        {
            _counter += _step;
        }
    }

    void reset() override
    {
        _counter = 0;
    }
};

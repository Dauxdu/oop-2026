export module counters:ICounter;

import std;

class ICounter
{
public:
    virtual ~ICounter() = default;
    virtual int get_value() const = 0;
    virtual std::string get_type() const = 0;
    virtual bool is_limit_reached() const = 0;
    virtual void increment() = 0;
    virtual void reset() = 0;
};

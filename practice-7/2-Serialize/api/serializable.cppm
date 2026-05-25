export module api:serializable;

import std;
import universal_value;

export class Serializable
{
public:
    virtual ~Serializable() = default;

    virtual Value to_value() const = 0;
};
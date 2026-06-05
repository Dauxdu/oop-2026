export module api:Serializable;

import std;
import UValue;

export class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual UValue to_value() const = 0;
};
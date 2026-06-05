export module api:Serializer;

import std;
import UValue;

export class Serializer
{
public:
    virtual ~Serializer() = default;
    virtual std::string serialize(const UValue &value) const = 0;
};
export module api:serializer;

import std;
import universal_value;

export class Serializer
{
public:
    virtual ~Serializer() = default;

    virtual std::string serialize(const Value &value) const = 0;
};
import std;
import UValue;
import serializers;

int main()
{
    User user{"Вишня", 30};
    UValue value = user.to_value();

    JsonSerializer js;
    XmlSerializer xs("PersonData");
    BinarySerializer bs;

    std::println("JSON: {}", js.serialize(value));
    std::println("XML: {}", xs.serialize(value));

    auto bin = bs.serialize(value);
    std::print("BIN: ");
    for (char c : bin)
    {
        std::print("{:02x} ", static_cast<unsigned char>(c));
    }
    std::println();

    return 0;
}
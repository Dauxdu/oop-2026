import std;
import implementations;
import universal_value;

int main()
{
    User user{"Вишня", 30};
    Value value = user.to_value();

    JsonSerializer js;
    XmlSerializer xs("PersonData");
    BinarySerializer bs;

    std::println("JSON: {}", js.serialize(value));
    std::println("XML: {}", xs.serialize(value));

    auto bin = bs.serialize(value);
    std::println("BIN: ");
    for (std::uint8_t c : bin)
    {
        std::print("{:02x} ", static_cast<unsigned>(c));
    }
    std::println();

    return 0;
}
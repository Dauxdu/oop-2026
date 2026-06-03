export module TextAnalyzer:IDataSource;
import std;

export namespace ta
{
    class IDataSource
    {
    public:
        virtual ~IDataSource() = default;
        virtual std::vector<std::string> read_words() const = 0;
    };
}
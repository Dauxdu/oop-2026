export module TextAnalyzer:FileDataSource;

import std;
import :IDataSource;

export namespace ta
{
    class FileDataSource final : public IDataSource
    {

    private:
        std::filesystem::path _path;

    public:
        explicit FileDataSource(std::filesystem::path path) : _path(std::move(path))
        {
            if (_path.empty())
            {
                throw std::invalid_argument("Путь к файлу не может быть пустым");
            }
        }

        FileDataSource() = delete;

        std::vector<std::string> read_words() const override
        {
            std::ifstream file(_path);
            if (!file)
            {
                throw std::runtime_error("Не удалось открыть файл: " + _path.string());
            }

            std::string word;
            std::vector<std::string> words;
            while (file >> word)
            {
                words.push_back(std::move(word));
            }

            if (file.bad())
            {
                throw std::runtime_error("Ошибка чтения файла: " + _path.string());
            }

            return words;
        }
    };
}
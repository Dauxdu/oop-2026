/**
 * @file IDataSource.cppm
 * @brief Интерфейс источника данных для текстового анализатора.
 */
export module TextAnalyzer:IDataSource;
import std;

export namespace ta
{
    /**
     * @brief Абстрактный интерфейс для чтения слов из источника.
     */
    class IDataSource
    {
    public:
        virtual ~IDataSource() = default;

        /**
         * @brief Читает все слова из источника.
         * @return Вектор строк, представляющих слова.
         * @throws std::runtime_error Если источник недоступен или произошла ошибка чтения.
         */
        virtual std::vector<std::string> read_words() const = 0;
    };
}
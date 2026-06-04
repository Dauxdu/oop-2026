/**
 * @file WordAnalyzer.cppm
 * @brief Модуль статистического анализа слов.
 */
export module TextAnalyzer:WordAnalyzer;
import std;

export namespace ta::WordAnalyzer
{
    /**
     * @brief Структура для хранения группы слов с одинаковой частотой.
     */
    struct WordFrequency
    {
        std::vector<std::string> words;
        std::size_t frequency;
    };

    /**
     * @brief Подсчитывает количество уникальных слов.
     * @param[in] words Вектор слов.
     * @return Количество уникальных элементов.
     */
    std::size_t count_unique_words(const std::vector<std::string> &words)
    {
        return std::unordered_set<std::string>(words.begin(), words.end()).size();
    }

    /**
     * @brief Фильтрует слова, удаляя незначимые (stop words).
     * @param[in] words Вектор слов для фильтрации.
     * @param[in] stop_words Набор незначимых слов.
     * @return Вектор слов без stop words.
     */
    std::vector<std::string> filter_words(const std::vector<std::string> &words, const std::unordered_set<std::string> &stop_words)
    {
        std::vector<std::string> result;
        for (const auto &word : words)
        {
            if (!stop_words.contains(word))
            {
                result.push_back(word);
            }
        }

        return result;
    }

    /**
     * @brief Находит топ-N самых частых слов.
     * @param[in] words Вектор проанализированных слов.
     * @param[in] n Количество слов для возврата.
     * @return Вектор структур WordFrequency, отсортированный по убыванию частоты.
     * @throws std::invalid_argument Если n == 0.
     */
    std::vector<WordFrequency> find_top_words(const std::vector<std::string> &words, std::size_t n)
    {
        if (n == 0)
        {
            throw std::invalid_argument("Параметр n должен быть больше 0");
        }

        if (words.empty())
        {
            return {};
        }

        std::unordered_map<std::string, std::size_t> counts;
        for (const auto &word : words)
        {
            ++counts[word];
        }

        std::unordered_map<std::size_t, std::vector<std::string>> freq_word_pairs;
        for (const auto &[word, count] : counts)
        {
            freq_word_pairs[count].push_back(word);
        }

        std::vector<std::size_t> unique_freqs;
        for (const auto &[freq, _] : freq_word_pairs)
        {
            unique_freqs.push_back(freq);
        }
        std::ranges::sort(unique_freqs, std::greater<>{});

        std::vector<WordFrequency> result;
        for (std::size_t freq : unique_freqs)
        {
            if (result.size() >= n)
            {
                break;
            }

            auto &list = freq_word_pairs[freq];
            std::ranges::sort(list);
            result.push_back(WordFrequency{std::move(list), freq});
        }

        return result;
    }
}

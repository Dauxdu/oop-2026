/**
 * @file TextNormalizer.cppm
 * @brief Модуль нормализации слов (приведение к нижнему регистру, очистка).
 */
export module TextAnalyzer:TextNormalizer;
import std;

export namespace ta::TextNormalizer
{
    /**
     * @brief Преобразует строку к нижнему регистру.
     * @param[in] word Исходное слово.
     * @return Слово в нижнем регистре.
     */
    std::string to_lower(std::string word)
    {
        for (char &c : word)
        {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return word;
    }

    /**
     * @brief Извлекает символьную часть слова, отбрасывая не буквы по краям.
     * @param[in] word Исходное слово.
     * @return Подстрока, содержащая только буквенную часть.
     */
    std::string_view extract_alpha_part(std::string_view word)
    {
        std::size_t first = 0;
        while (first < word.size() && !std::isalpha(word[first]))
        {
            ++first;
        }

        std::size_t last = word.size();
        while (last > first && !std::isalpha(word[last - 1]))
        {
            --last;
        }

        if (first >= last)
        {
            return {};
        }

        return word.substr(first, last - first);
    }

    /**
     * @brief Проверяет, является ли слово валидным.
     * @details Валидное слово состоит из букв и/или одинарных дефисов внутри.
     * @param[in] word Нормализованное слово.
     * @return true если слово валидно, иначе false.
     */
    bool is_valid_word(std::string_view word)
    {
        if (word.empty() || word.front() == '-' || word.back() == '-')
        {
            return false;
        }

        for (char c : word)
        {
            if (!std::isalpha(static_cast<unsigned char>(c)) && c != '-')
            {
                return false;
            }
        }

        for (std::size_t i = 1; i < word.size(); ++i)
        {
            if (word[i] == '-' && word[i - 1] == '-')
            {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Полностью нормализует одно слово.
     * @param[in] word Исходное слово.
     * @return Нормализованное слово или пустая строка, если слово невалидно.
     */
    std::string normalize_word(std::string word)
    {
        if (word.empty())
        {
            return {};
        }

        word = to_lower(word);

        std::string_view str = extract_alpha_part(word);
        if (str.empty() || !is_valid_word(str))
        {
            return {};
        }

        return std::string(str);
    }

    /**
     * @brief Нормализует коллекцию слов.
     * @param[in] words Вектор исходных слов.
     * @return Вектор нормализованных валидных слов.
     */
    std::vector<std::string> normalize_words(const std::vector<std::string> &words)
    {
        std::vector<std::string> result;
        for (const auto &word : words)
        {
            auto normalized = normalize_word(word);
            if (!normalized.empty())
            {
                result.push_back(std::move(normalized));
            }
        }

        return result;
    }
}

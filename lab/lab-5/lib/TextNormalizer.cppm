export module TextAnalyzer:TextNormalizer;
import std;

export namespace ta::TextNormalizer
{
    std::string to_lower(std::string word)
    {
        for (char &c : word)
        {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return word;
    }

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

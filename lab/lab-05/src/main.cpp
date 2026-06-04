/**
 * @file main.cpp
 * @brief Точка входа в приложение анализа текстов.
 */
import std;
import inx;
import console;
import TextAnalyzer;

/**
 * @brief Точка входа в программу.
 * @details Запускает интерактивный цикл анализа файлов.
 * @return 0 при успешном завершении.
 */
int main()
{
    print_header(5);

    std::println("Привет, {}, это программа для анализа текстового файла.\n", get_system_username());

    while (true)
    {
        try
        {
            std::print("Введите путь к файлу (или Enter для выхода): ");
            std::string path;
            std::getline(std::cin, path);

            if (path.empty())
            {
                std::println("Завершение работы программы.");
                break;
            }

            ta::FileDataSource source(path);
            auto raw_words = source.read_words();

            auto words = ta::TextNormalizer::normalize_words(raw_words);

            std::print("Введите путь к файлу незначимых слов (или Enter, если нет): ");
            std::string stop_words_path;
            std::getline(std::cin, stop_words_path);

            std::unordered_set<std::string> stop_words_set;
            if (!stop_words_path.empty())
            {
                ta::FileDataSource stop_source(stop_words_path);
                auto raw_stop_words = stop_source.read_words();
                auto stop_words = ta::TextNormalizer::normalize_words(raw_stop_words);
                stop_words_set = std::ranges::to<std::unordered_set>(stop_words);
            }

            auto filtered_words = ta::WordAnalyzer::filter_words(words, stop_words_set);
            std::println("Общее количество слов: {}", filtered_words.size());
            std::println("Количество уникальных слов: {}", ta::WordAnalyzer::count_unique_words(filtered_words));

            if (!filtered_words.empty())
            {
                std::size_t n = inx::input_numeric<std::size_t>("\nВведите количество для самых частых слов: ", 1);

                auto top_words = ta::WordAnalyzer::find_top_words(filtered_words, n);

                std::println("\nТоп слов:");
                for (const auto &[words_list, frequency] : top_words)
                {
                    std::print("{}: ", frequency);
                    for (const auto &word : words_list)
                    {
                        std::print("\"{}\" ", word);
                    }
                    std::println();
                }
            }
            std::println();
        }
        catch (const std::runtime_error &e)
        {
            std::println("Ошибка: {}", e.what());
            throw;
        }
        catch (const std::exception &e)
        {
            std::println("Ошибка: {}", e.what());
        }
    }

    return 0;
}
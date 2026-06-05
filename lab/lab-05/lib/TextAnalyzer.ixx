/**
 * @file TextAnalyzer.ixx
 * @brief Главный интерфейс модуля TextAnalyzer.
 * @details Агрегирует и экспортирует все компоненты системы анализа текста.
 */
export module TextAnalyzer;

export import :IDataSource;
export import :FileDataSource;
export import :TextNormalizer;
export import :WordAnalyzer;

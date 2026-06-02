/**
 * @file main.cpp
 * @brief Интерактивное консольное приложение для управления вектором целых чисел.
 * @details Предоставляет меню для изменения размера, обновления элементов,
 *          случайного заполнения и вычисления суммы вектора.
 */
import std;
import inx;
import console;
import Vector;

/**
 * @brief Выводит меню доступных операций в консоль.
 */
void print_menu()
{
  std::println("[1] Изменить размер");
  std::println("[2] Изменить элемент");
  std::println("[3] Заполнить случайным образом");
  std::println("[4] Вычислить сумму");
  std::println("[5] Выход\n");
  std::print("Выберите пункт меню: ");
}

/**
 * @brief Форматирует и выводит содержимое вектора в виде списка.
 * @param[in] vec Вектор для отображения.
 */
void print_vec(const std::vector<int> &vec)
{
  std::print("[");

  for (const int &x : vec)
  {
    std::print("{}", x);
    if (&x != &vec.back())
    {
      std::print(", ");
    }
  }
  std::println("]\n");
}

/**
 * @brief Изменяет размер вектора на основе пользовательского ввода.
 * @param[in, out] vec Ссылка на изменяемый вектор.
 */
void resize_vector(std::vector<int> &vec)
{
  std::print("Введите новый размер вектора: ");
  vec.resize(inx::input_numeric<int>(0));
}

/**
 * @brief Обновляет значение элемента вектора по пользовательскому индексу.
 * @param[in, out] vec Ссылка на вектор.
 *
 * @throws std::invalid_argument Если вектор пуст.
 */
void update_vector(std::vector<int> &vec)
{
  if (vec.empty())
  {
    throw std::invalid_argument("Вектор пуст.");
  }

  std::print("Введите индекс элемента (1-{}): ", vec.size());
  int index = inx::input_numeric<int>(1, vec.size());

  std::print("Введите новое значение для элемента {}: ", index);
  int value = inx::input_numeric<int>();

  vec[index - 1] = value;
}

/**
 * @brief Заполняет вектор псевдослучайными числами в заданном диапазоне.
 * @param[in, out] vec Ссылка на вектор.
 * @throws std::invalid_argument Если вектор пуст.
 */
void fill_vector(std::vector<int> &vec)
{
  if (vec.empty())
  {
    throw std::invalid_argument("Вектор пуст.");
  }

  int min_val = inx::input_numeric<int>("Введите минимум: ");
  int max_val = inx::input_numeric<int>("Введите максимум: ", min_val);

  fill_random(vec, min_val, max_val);
}

/**
 * @brief Вычисляет и выводит сумму элементов вектора.
 * @param[in] vec Ссылка на вектор.
 * @throws std::invalid_argument Если вектор пуст.
 */
void sum_vector(const std::vector<int> &vec)
{
  if (vec.empty())
  {
    throw std::invalid_argument("Ошибка: вектор пуст.");
  }

  int sum = calculate_sum(vec);
  std::println("-----------------------------------------------");
  std::println("Количество элементов: {}", vec.size());
  std::println("Сумма элементов: {}", sum);
}

/**
 * @brief Точка входа программы.
 * @details Запускает цикл обработки меню, делегирует операции вспомогательным
 *          функциям и перехватывает исключения для предотвращения краша приложения.
 * @return 0 при успешном завершении.
 */
int main()
{
  print_header(2);

  std::println("Привет, {}, это меню управления вектором.", get_system_username());
  std::println("-----------------------------------------------");

  std::vector<int> vec;

  while (true)
  {
    try
    {
      std::print("Вектор: ");
      print_vec(vec);
      print_menu();

      int choice = inx::input_numeric<int>(1, 5);

      switch (choice)
      {
      case 1:
        resize_vector(vec);
        break;
      case 2:
        update_vector(vec);
        break;
      case 3:
        fill_vector(vec);
        break;
      case 4:
        sum_vector(vec);
        break;
      case 5:
        std::println("До свидания!");
        return 0;
      }
      std::println("-----------------------------------------------");
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
}

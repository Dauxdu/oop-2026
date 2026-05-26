#include <SFML/Graphics.hpp>

import std;
import API;
import TicTacToe;

int main()
{
    std::println("[SYSTEM] Запуск приложения...");
    sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);
    std::println("[WINDOW] Окно создано: 1024x1024");

    window.setFramerateLimit(10);

    auto game = tictactoe::make(1024, 1024);
    std::println("[GAME] Объект игры инициализирован");

    sf::Clock clock;
    std::println("[LOOP] Игровой цикл запущен (FPS limit: 10)");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                std::println("[SYSTEM] Получен сигнал закрытия окна");
                window.close();
            }

            if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    std::println("[INPUT] Нажата клавиша [ESC] -> Закрытие приложения");
                    window.close();
                }

                if (key->scancode == sf::Keyboard::Scancode::R)
                {
                    std::println("[INPUT] Нажата клавиша [R] -> Сброс игры");
                    game->reset();
                }

                if (key->scancode == sf::Keyboard::Scancode::M)
                {
                    std::println("[INPUT] Нажата клавиша [M] -> Переключение звука");
                    game->toggle_mute();
                }
            }

            game->handle_event(*event);
        }

        game->update(clock.restart().asSeconds());

        window.clear();
        game->draw(window);
        window.display();
    }

    std::println("[SYSTEM] Приложение завершено успешно");
    return 0;
}
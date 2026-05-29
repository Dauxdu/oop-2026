#include <SFML/Graphics.hpp>

import std;
import TicTacToe;

int main()
{
    std::println("[SYSTEM] Starting application");
    constexpr unsigned window_size = 1024;

    sf::RenderWindow window(sf::VideoMode({window_size, window_size}), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);
    tictactoe::Game game{{static_cast<float>(window_size), static_cast<float>(window_size)}};

    window.setIcon(*game.icon());
    window.setFramerateLimit(60);
    std::println("[WINDOW] Created window");

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            game.handle_event(*event, window);
        }

        game.update(clock.restart().asSeconds());

        window.clear();

        game.draw(window);

        window.display();
    }

    std::println("[SYSTEM] Shutdown complete");
    return 0;
}
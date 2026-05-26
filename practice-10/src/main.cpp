#include <SFML/Graphics.hpp>

import API;
import TicTacToe;

int main()
{
    sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Tic Tac Toe");

    window.setFramerateLimit(10);

    auto game = tictactoe::make(1024, 1024);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }

            game->handle_event(*event);
        }

        const float dt = clock.restart().asSeconds();

        game->update(dt);

        window.clear();
        game->draw(window);
        window.display();
    }
}
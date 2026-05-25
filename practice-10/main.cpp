#include <SFML/Graphics.hpp>
import api;
import tictactoe;

int main()
{
    constexpr unsigned WIDTH = 1024;
    constexpr unsigned HEIGHT = 1024;

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Tic Tac Toe");
    window.setFramerateLimit(10);

    auto game = tictactoe::make(WIDTH, HEIGHT);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            game->handle_event(*event);
        }

        const float dt = clock.restart().asSeconds();
        game->update(dt);

        window.clear(sf::Color::Black);
        game->draw(window);
        window.display();
    }

    return 0;
}
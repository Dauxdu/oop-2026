#include <SFML/Graphics.hpp>

import std;
import TicTacToe;

int main()
{
    std::println("[SYSTEM] Starting application");
    tictactoe::Game game{"assets"};
    sf::RenderWindow window{sf::VideoMode{{800, 800}}, "Tic Tac Toe"};

    window.setIcon(game.get_icon());
    window.setVerticalSyncEnabled(true);

    std::println("[WINDOW] Created window with size {}x{}", window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            game.handle_event(*event, window);
        }

        game.draw(window);
    }

    std::println("[SYSTEM] Shutdown complete");
    return 0;
}
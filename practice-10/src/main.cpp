#include <SFML/Graphics.hpp>

import std;
import Config;
import TicTacToe;

int main()
{
    config::Manager cfg{};

    std::println("[SYSTEM] Starting application");

    tictactoe::Game game{"assets"};
    sf::RenderWindow window{sf::VideoMode{{cfg.window().width, cfg.window().height}}, "Tic Tac Toe"};

    window.setIcon(game.get_icon());

    if (cfg.window().vsync)
    {
        window.setVerticalSyncEnabled(cfg.window().vsync);
    }
    else
    {
        window.setFramerateLimit(cfg.window().fps);
    }

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
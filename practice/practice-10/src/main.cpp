#include <SFML/Graphics.hpp>

import std;
import Config;
import TicTacToe;

int main()
{
    try
    {
        std::println("[SYSTEM] Starting application");
        config::Manager cfg;
        tictactoe::Game game{"assets", cfg};

        sf::RenderWindow window{sf::VideoMode{{cfg.window().width, cfg.window().height}}, "Tic Tac Toe"};
        window.setIcon(game.get_icon());

        window.setVerticalSyncEnabled(cfg.window().vsync);
        if (!cfg.window().vsync)
        {
            window.setFramerateLimit(cfg.window().fps);
        }

        std::println("[WINDOW] Created window with size {}x{}", window.getSize().x, window.getSize().y);

        std::println("[APP] Audio: mute={}, master={}, sfx={}", cfg.audio().mute, cfg.audio().master_volume, cfg.audio().sfx_volume);

        while (window.isOpen())
        {
            while (auto event = window.pollEvent())
            {
                game.handle_event(*event, window);
            }
            game.draw(window);
        }

        std::println("[SYSTEM] Shutdown complete");
        return 0;
    }
    catch (const std::exception &e)
    {
        std::println(stderr, "[FATAL ERROR] {}", e.what());
        return 1;
    }
}

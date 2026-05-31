#include <SFML/Graphics.hpp>

import std;
import Config;
import TicTacToe;

int main()
{
    std::println("[SYSTEM] Starting application");
    config::Manager cfg;
    tictactoe::Game game{"assets", cfg};
    sf::RenderWindow window{sf::VideoMode{{cfg.window().width, cfg.window().height}}, "Tic Tac Toe"};

    window.setIcon(game.get_icon());

    if (cfg.window().vsync)
    {
        window.setVerticalSyncEnabled(true);
    }
    else
    {
        window.setFramerateLimit(cfg.window().fps);
    }
    std::println("[WINDOW] Created window with size {}x{}", window.getSize().x, window.getSize().y);

    game.set_muted(cfg.audio().mute);
    game.set_audio_levels(cfg.audio().master_volume, cfg.audio().sfx_volume);

    std::println("[APP] Audio: mute={}, master={}, sfx={}", cfg.audio().mute ? "on" : "off", cfg.audio().master_volume, cfg.audio().sfx_volume);

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
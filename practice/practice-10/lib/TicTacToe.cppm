module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module TicTacToe;

import std;
import Assets;
import Audio;
import Config;
import GameLogic;
import Renderer;

export namespace tictactoe
{
    class Game final
    {
    private:
        assets::Manager _assets;
        renderer::Renderer _renderer;
        game_logic::Board _board;
        audio::Manager _audio;

        sf::Color _background_color{30, 30, 46};

    public:
        Game(const Game &) = delete;
        Game &operator=(const Game &) = delete;
        Game(Game &&) = delete;
        Game &operator=(Game &&) = delete;

        explicit Game(const std::filesystem::path &asset_dir, const config::Manager &cfg) : _assets{asset_dir}, _renderer{_assets}, _audio{_assets}
        {
            _audio.set_muted(cfg.audio().mute);
            _audio.set_audio_levels(cfg.audio().master_volume, cfg.audio().sfx_volume);
        }

        [[nodiscard]] const sf::Image &get_icon() const noexcept { return _assets.get_image(assets::ImageID::Icon); }

        [[nodiscard]] sf::Color get_background_color() const noexcept { return _background_color; }

        void set_background_color(sf::Color color) noexcept { _background_color = color; }

        void draw(sf::RenderWindow &window) const
        {
            window.clear(_background_color);
            _renderer.render(window, _board);
            window.display();
        }

        void handle_event(const sf::Event &event, sf::RenderWindow &window)
        {
            if (event.is<sf::Event::Closed>())
            {
                window.close();
                return;
            }

            if (const auto *key = event.getIf<sf::Event::KeyPressed>())
            {
                switch (key->scancode)
                {
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    return;
                case sf::Keyboard::Scancode::R:
                    _board.reset();
                    return;
                case sf::Keyboard::Scancode::M:
                    _audio.toggle_mute();
                    return;
                default:
                    break;
                }
            }

            if (const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button != sf::Mouse::Button::Left || _board.is_game_over())
                {
                    return;
                }

                const auto coords = _renderer.to_board_coords({mouse->position.x, mouse->position.y}, window);

                if (_board.is_make_move(coords.x, coords.y))
                {
                    _audio.play(assets::SoundID::Click);

                    if (_board.is_game_over())
                    {
                        const auto result = _board.get_game_result();
                        if (result == game_logic::GameResult::XWins || result == game_logic::GameResult::OWins)
                        {
                            _audio.play(assets::SoundID::Win);
                            return;
                        }

                        _audio.play(assets::SoundID::Draw);
                    }
                }
            }
        }
    };
}
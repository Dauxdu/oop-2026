module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module TicTacToe;

import std;
import Assets;
import GameLogic;
import Renderer;

export namespace tictactoe
{
    class Game final
    {
    private:
        assets::Manager _assets;
        game_logic::Board _board;
        renderer::Renderer _renderer;

        bool _muted{false};
        std::optional<sf::Sound> _win_sound;
        std::optional<sf::Sound> _click_sound;
        sf::Color _background_color{30, 30, 46};

        void play_sound(std::optional<sf::Sound> &sound) const noexcept
        {
            if (!_muted && sound.has_value())
            {
                sound->play();
            }
        }

    public:
        explicit Game(const std::filesystem::path &asset_dir) : _assets{asset_dir}, _renderer{_assets}
        {
            try
            {
                _click_sound.emplace(_assets.get_sound(assets::SoundID::Click));
                _click_sound->setVolume(100.f);
            }
            catch (const std::exception &)
            {
                std::println("Failed to load click sound");
            }

            try
            {
                _win_sound.emplace(_assets.get_sound(assets::SoundID::Win));
                _win_sound->setVolume(30.f);
            }
            catch (const std::exception &)
            {
                std::println("Failed to load win sound");
            }
        }

        [[nodiscard]]
        const sf::Image &get_icon() const noexcept
        {
            return _assets.get_image(assets::ImageID::Icon);
        }

        [[nodiscard]]
        sf::Color get_background_color() const noexcept
        {
            return _background_color;
        }

        void set_background_color(sf::Color color) noexcept
        {
            _background_color = color;
        }

        void draw(sf::RenderWindow &window) const noexcept
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
                    _muted = !_muted;
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

                if (_board.is_move_cell(coords.x, coords.y))
                {
                    play_sound(_click_sound);

                    if (_board.is_game_over())
                    {
                        play_sound(_win_sound);
                    }
                }
            }
        }
    };
}
module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module TicTacToe;

import std;
import Assets;
import Config;
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
        explicit Game(const std::filesystem::path &asset_dir, const config::Manager &cfg) : _assets{asset_dir}, _renderer{_assets}
        {
            try
            {
                _click_sound.emplace(_assets.get_sound(assets::SoundID::Click));
                _click_sound->setVolume(cfg.audio().sfx_volume);
            }
            catch (const std::exception &)
            {
                std::println("Failed to load click sound");
            }

            try
            {
                _win_sound.emplace(_assets.get_sound(assets::SoundID::Win));
                _win_sound->setVolume(cfg.audio().sfx_volume);
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

        void set_muted(bool muted) noexcept
        {
            _muted = muted;
        }

        void set_sfx_volume(float volume) noexcept
        {
            const float clamped = std::clamp(volume, 0.f, 100.f);
            if (_click_sound)
            {
                _click_sound->setVolume(clamped);
            }

            if (_win_sound)
            {
                _win_sound->setVolume(clamped);
            }
        }

        void set_audio_levels(float master, float sfx) noexcept
        {
            const float master_clamped = std::clamp(master, 0.f, 100.f);
            const float sfx_clamped = std::clamp(sfx, 0.f, 100.f);
            const float final_sfx = (master_clamped * sfx_clamped) / 100.f;

            if (_click_sound)
            {
                _click_sound->setVolume(final_sfx);
            }

            if (_win_sound)
            {
                _win_sound->setVolume(final_sfx);
            }
        }

        void set_background_color(sf::Color color) noexcept
        {
            _background_color = color;
        }

        void toggle_mute() noexcept
        {
            _muted = !_muted;
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
                    toggle_mute();
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
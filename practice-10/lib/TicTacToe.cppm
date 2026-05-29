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
        sf::Vector2f _size;

        assets::Manager _assets;

        std::optional<sf::Sound> _click;
        std::optional<sf::Sound> _win;

        game_logic::Board _board;
        renderer::Renderer _renderer;

        bool _muted{false};

        void play_sound(std::optional<sf::Sound> &sound)
        {
            if (!_muted && sound)
            {
                sound->play();
            }
        }

    public:
        Game(sf::Vector2f size) : _size{size}, _assets{"assets"}, _renderer{size, _assets}
        {
            if (const auto *buffer = _assets.get_click_sound())
            {
                _click.emplace(*buffer);
                _click->setVolume(100.f);
            }

            if (const auto *buffer = _assets.get_win_sound())
            {
                _win.emplace(*buffer);
                _win->setVolume(30.f);
            }
        }

        [[nodiscard]]
        const sf::Image *icon() const noexcept
        {
            return _assets.get_icon();
        }

        void update(float) {}

        void draw(sf::RenderTarget &target) const
        {
            _renderer.render(target, _board);
        }

        void reset() noexcept
        {
            _board.reset();
        }

        void handle_event(const sf::Event &event, sf::RenderWindow &window)
        {
            if (const auto *key = event.getIf<sf::Event::KeyPressed>())
            {
                switch (key->scancode)
                {
                case sf::Keyboard::Scancode::Escape:
                {
                    window.close();

                    return;
                }

                case sf::Keyboard::Scancode::R:
                {
                    reset();

                    return;
                }
                case sf::Keyboard::Scancode::M:
                {
                    _muted = !_muted;

                    return;
                }
                default:
                {
                    break;
                }
                }
            }

            const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();
            if (!mouse || mouse->button != sf::Mouse::Button::Left || _board.is_game_over())
            {
                return;
            }

            const int x = mouse->position.x / (_size.x / game_logic::Board::size);
            const int y = mouse->position.y / (_size.y / game_logic::Board::size);

            if (_board.move_cell(x, y))
            {
                play_sound(_click);

                if (_board.is_game_over())
                {
                    play_sound(_win);
                }
            }
        }
    };
}
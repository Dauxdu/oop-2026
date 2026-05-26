module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module TicTacToe;

import API;
import Assets;
import GameLogic;
import Renderer;

export namespace tictactoe
{
    class Game final : public api::IGame
    {
        float _width{};
        float _height{};

        assets::Manager _assets;
        std::optional<sf::Sound> _click;
        std::optional<sf::Sound> _win;

        game_logic::Board _board;
        renderer::Renderer _renderer;

    public:
        Game(float width, float height) : _width{width}, _height{height}, _assets{"assets"}, _renderer{width, height, _assets}
        {
            if (const auto *b = _assets.win_sound())
            {
                _win.emplace(*b);
                _win->setVolume(30.f);
            }

            if (const auto *b = _assets.click_sound())
            {
                _click.emplace(*b);
                _click->setVolume(100.f);
            }
        }

        void update(float) override {}

        void handle_event(const sf::Event &event) override
        {
            const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();

            if (!mouse || mouse->button != sf::Mouse::Button::Left || _board.is_over())
            {
                return;
            }

            const int x = mouse->position.x / (_width / 3.f);
            const int y = mouse->position.y / (_height / 3.f);

            if (_board.move(x, y))
            {
                if (_click)
                {
                    _click->play();
                }

                if (_board.is_over() && _win)
                {
                    _win->play();
                }
            }
        }

        void draw(sf::RenderTarget &target) const override
        {
            _renderer.render(target, _board);
        }
    };

    [[nodiscard]]
    inline api::GamePtr make(float width, float height)
    {
        return std::make_unique<Game>(width, height);
    }
}
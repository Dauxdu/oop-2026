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
        game_logic::Board _board;
        renderer::Renderer _renderer;
        std::optional<sf::Sound> _win_sound;

    public:
        Game(float width, float height) : _width{width}, _height{height}, _assets{"assets"}, _renderer{width, height, _assets}
        {
            if (const auto *buffer = _assets.win_sound())
            {
                _win_sound.emplace(*buffer);
                _win_sound->setVolume(0.f);
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

            if (_board.move(x, y) && _board.is_over())
            {
                _win_sound->play();
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
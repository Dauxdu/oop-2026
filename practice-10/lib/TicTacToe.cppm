module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module TicTacToe;

import API;
import Assets;
import GameLogic;
import Render;

export namespace TicTacToe
{
    class Game final : public API::IGame
    {
        Assets::Manager _assets;
        GameLogic::Logic _logic;
        Render::Render _renderer;
        std::optional<sf::Sound> _win_sound;

    public:
        Game(float width, float height) : _assets{"assets"}, _renderer{width, height, _assets}
        {
            if (const auto *buffer = _assets.win_sound())
            {
                _win_sound.emplace(*buffer);
                _win_sound->setVolume(0.f);
            }
        }

        void update(float) override final {}

        void handle_event(const sf::Event &event) override
        {
            const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();

            if (!mouse || mouse->button != sf::Mouse::Button::Left || _logic.is_over())
            {
                return;
            }

            const int x = static_cast<int>(mouse->position.x / _renderer.cell_width());

            const int y = static_cast<int>(mouse->position.y / _renderer.cell_height());

            if (_logic.move(x, y) && _logic.is_over())
            {
                if (_win_sound)
                {
                    _win_sound->play();
                }
            }
        }

        void draw(sf::RenderTarget &target) const override
        {
            _renderer.render(target, _logic);
        }
    };

    [[nodiscard]]
    inline API::GamePtr make(float width, float height)
    {
        return std::make_unique<Game>(width, height);
    }
}
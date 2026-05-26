module;

#include <SFML/Graphics.hpp>

export module Render;

import std;

import Assets;
import GameLogic;

export namespace Render
{
    class Render
    {
        static constexpr float MARK_SCALE = 0.8f;

        float _width{};
        float _height{};

        const Assets::Manager &_assets;

        [[nodiscard]]
        float cw() const noexcept
        {
            return _width / GameLogic::BOARD_SIZE;
        }

        [[nodiscard]]
        float ch() const noexcept
        {
            return _height / GameLogic::BOARD_SIZE;
        }

        void draw_mark(sf::RenderTarget &target, const sf::Texture &texture, sf::Vector2f center) const
        {
            sf::Sprite sprite{texture};

            const float scale = (std::min(cw(), ch()) * MARK_SCALE) / std::max(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y));

            sprite.setOrigin(sprite.getLocalBounds().getCenter());

            sprite.setScale({scale, scale});
            sprite.setPosition(center);

            target.draw(sprite);
        }

        void draw_grid(sf::RenderTarget &target) const
        {
            sf::RectangleShape line;

            line.setFillColor(sf::Color{200, 200, 200});

            for (int i = 1; i < GameLogic::BOARD_SIZE; ++i)
            {
                line.setSize({2.f, _height});
                line.setPosition({i * cw(), 0.f});

                target.draw(line);

                line.setSize({_width, 2.f});
                line.setPosition({0.f, i * ch()});

                target.draw(line);
            }
        }

    public:
        Render(float width, float height, const Assets::Manager &assets) : _width{width}, _height{height}, _assets{assets} {}

        void render(sf::RenderTarget &target, const GameLogic::Logic &logic) const
        {
            if (const auto *board = _assets.board())
            {
                sf::Sprite sprite{*board};

                sprite.setScale({_width / board->getSize().x, _height / board->getSize().y});

                target.draw(sprite);
            }
            else
            {
                target.clear(sf::Color{30, 30, 40});

                draw_grid(target);
            }

            for (int y = 0; y < GameLogic::BOARD_SIZE; ++y)
            {
                for (int x = 0; x < GameLogic::BOARD_SIZE; ++x)
                {
                    const auto cell = logic.get(x, y);

                    if (cell == Cell::Empty)
                    {
                        continue;
                    }

                    const auto *texture = _assets.mark(cell);

                    if (!texture)
                    {
                        continue;
                    }

                    const sf::Vector2f center{x * cw() + cw() / 2.f, y * ch() + ch() / 2.f};

                    draw_mark(target, *texture, center);
                }
            }

            if (logic.is_over() && _assets.overlay(logic.result()))
            {
                sf::Sprite overlay{*_assets.overlay(logic.result())};

                overlay.setScale({_width / overlay.getTexture().getSize().x, _height / overlay.getTexture().getSize().y});

                target.draw(overlay);
            }
        }

        [[nodiscard]]
        float cell_width() const noexcept
        {
            return cw();
        }

        [[nodiscard]]
        float cell_height() const noexcept
        {
            return ch();
        }
    };
}
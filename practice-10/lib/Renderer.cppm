module;

#include <SFML/Graphics.hpp>

export module Renderer;

import std;
import Assets;
import GameLogic;

export namespace renderer
{
    class Renderer
    {
    private:
        const assets::Manager &_assets;

        float _width{};
        float _height{};

        [[nodiscard]]
        float cell_width() const noexcept
        {
            return _width / 3.f;
        }

        [[nodiscard]]
        float cell_height() const noexcept
        {
            return _height / 3.f;
        }

        void draw_mark(sf::RenderTarget &target, const sf::Texture &texture, sf::Vector2f center) const
        {
            sf::Sprite sprite{texture};

            float min_scale = std::min(cell_width(), cell_height()) * 0.7f;
            float max_scale = std::max(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y));
            const float scale = (min_scale / max_scale);

            sprite.setOrigin(sprite.getLocalBounds().getCenter());
            sprite.setScale({scale, scale});
            sprite.setPosition(center);

            target.draw(sprite);
        }

    public:
        Renderer(float width, float height, const assets::Manager &assets) : _width{width}, _height{height}, _assets{assets} {}

        void render(sf::RenderTarget &target, const game_logic::Board &board) const
        {
            if (const auto *texture = _assets.board())
            {
                sf::Sprite sprite{*texture};

                sprite.setScale({_width / texture->getSize().x, _height / texture->getSize().y});

                target.draw(sprite);
            }

            const float cw = cell_width();
            const float ch = cell_height();
            for (int y = 0; y < 3; ++y)
            {
                for (int x = 0; x < 3; ++x)
                {
                    const Cell cell = board.get(x, y);

                    if (cell == Cell::Empty)
                    {
                        continue;
                    }

                    const auto *texture = _assets.mark_texture(cell);

                    if (!texture)
                    {
                        continue;
                    }

                    draw_mark(target, *texture, {x * cw + cw / 2.f, y * ch + ch / 2.f});
                }
            }

            if (const auto *overlay = _assets.overlay_texture(board.result()))
            {
                sf::Sprite sprite{*overlay};

                sprite.setScale({_width / overlay->getSize().x, _height / overlay->getSize().y});

                target.draw(sprite);
            }
        }
    };
}
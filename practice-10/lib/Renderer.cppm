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
        sf::Vector2f _size;

        [[nodiscard]]
        float cell_width() const noexcept
        {
            return _size.x / game_logic::Board::size;
        }

        [[nodiscard]]
        float cell_height() const noexcept
        {
            return _size.y / game_logic::Board::size;
        }

        void draw_mark(sf::RenderTarget &target, const sf::Texture &texture, sf::Vector2f center) const
        {
            sf::Sprite sprite{texture};

            const float target_size = std::min(cell_width(), cell_height()) * 0.7f;

            const float texture_size = std::max(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y));

            const float scale = target_size / texture_size;

            sprite.setOrigin(sprite.getLocalBounds().getCenter());
            sprite.setPosition(center);
            sprite.setScale({scale, scale});

            target.draw(sprite);
        }

    public:
        Renderer(sf::Vector2f size, const assets::Manager &assets) : _assets{assets}, _size{size} {}

        void render(sf::RenderTarget &target, const game_logic::Board &board) const
        {
            if (const auto *texture = _assets.get_board())
            {
                sf::Sprite sprite{*texture};

                sprite.setScale({_size.x / texture->getSize().x, _size.y / texture->getSize().y});

                target.draw(sprite);
            }

            const float cw = cell_width();
            const float ch = cell_height();

            for (int y = 0; y < game_logic::Board::size; ++y)
            {
                for (int x = 0; x < game_logic::Board::size; ++x)
                {
                    const Cell cell = board.get_cell(x, y);

                    if (cell == Cell::Empty)
                    {
                        continue;
                    }

                    const auto *texture = _assets.get_mark_texture(cell);

                    if (!texture)
                    {
                        continue;
                    }

                    draw_mark(target, *texture, {x * cw + cw / 2.f, y * ch + ch / 2.f});
                }
            }

            if (const auto *overlay = _assets.get_overlay_texture(board.get_game_result()))
            {
                sf::Sprite sprite{*overlay};

                sprite.setScale({_size.x / overlay->getSize().x, _size.y / overlay->getSize().y});

                target.draw(sprite);
            }
        }
    };
}
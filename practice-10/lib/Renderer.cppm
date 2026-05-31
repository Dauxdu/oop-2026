module;

#include <SFML/Graphics.hpp>

export module Renderer;

import std;
import Assets;
import GameLogic;

export namespace renderer
{
    class Renderer final
    {
    private:
        const assets::Manager &_assets;

        [[nodiscard]]
        static sf::FloatRect get_viewport(sf::Vector2u window_size) noexcept
        {
            const float window_aspect = static_cast<float>(window_size.x) / static_cast<float>(window_size.y);
            if (window_aspect >= 1.0f)
            {
                const float w = 1.0f / window_aspect;
                return {{(1.0f - w) / 2.0f, 0.0f}, {w, 1.0f}};
            }
            else
            {
                return {{0.0f, (1.0f - window_aspect) / 2.0f}, {1.0f, window_aspect}};
            }
        }

        [[nodiscard]]
        static constexpr sf::View create_game_view(sf::Vector2u window_size) noexcept
        {
            sf::View view{{1.5f, 1.5f}, {3.f, 3.f}};
            view.setViewport(get_viewport(window_size));

            return view;
        }

        void draw_target(sf::RenderTarget &target, const sf::Texture &texture, sf::Vector2f position, sf::Vector2f max_size) const noexcept
        {
            sf::Sprite sprite{texture};
            const float texture_width = static_cast<float>(texture.getSize().x);
            const float texture_height = static_cast<float>(texture.getSize().y);
            const float scale = std::min(max_size.x / texture_width, max_size.y / texture_height);

            sprite.setScale({scale, scale});
            const auto bounds = sprite.getLocalBounds();
            sprite.setOrigin(bounds.position + bounds.size / 2.f);
            sprite.setPosition(position);
            target.draw(sprite);
        }

    public:
        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;
        Renderer(Renderer &&) = delete;
        Renderer &operator=(Renderer &&) = delete;

        explicit Renderer(const assets::Manager &assets) : _assets{assets} {}

        void render(sf::RenderTarget &target, const game_logic::Board &board) const
        {
            target.setView(create_game_view(target.getSize()));

            draw_target(target, _assets.get_texture(assets::TextureID::Board), {1.5f, 1.5f}, {3.0f, 3.0f});

            const int board_size = board.get_board_size();
            for (int y = 0; y < board_size; ++y)
            {
                for (int x = 0; x < board_size; ++x)
                {
                    const auto cell = board.get_cell(x, y);
                    if (cell == game_logic::Cell::Empty)
                    {
                        continue;
                    }

                    assets::TextureID texture_id;
                    if (cell == game_logic::Cell::X)
                    {
                        texture_id = assets::TextureID::X;
                    }
                    else
                    {
                        texture_id = assets::TextureID::O;
                    }

                    draw_target(target, _assets.get_texture(texture_id), {static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f}, {0.7f, 0.7f});
                }
            }

            const auto result = board.get_game_result();
            if (result != game_logic::GameResult::None)
            {
                assets::TextureID texture_id;
                if (result == game_logic::GameResult::XWins)
                {
                    texture_id = assets::TextureID::XWin;
                }
                else if (result == game_logic::GameResult::OWins)
                {
                    texture_id = assets::TextureID::OWin;
                }
                else
                {
                    texture_id = assets::TextureID::Draw;
                }

                draw_target(target, _assets.get_texture(texture_id), {1.5f, 1.5f}, {3.0f, 3.0f});
            }
        }

        [[nodiscard]]
        sf::Vector2i to_board_coords(sf::Vector2i mouse_pixel, const sf::RenderTarget &target) const noexcept
        {
            const auto logical = target.mapPixelToCoords(mouse_pixel, create_game_view(target.getSize()));

            return {static_cast<int>(std::floor(logical.x)), static_cast<int>(std::floor(logical.y))};
        }
    };
}
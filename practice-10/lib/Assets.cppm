module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module Assets;

import std;
import GameLogic;

export namespace assets
{
    class Manager
    {
    private:
        std::optional<sf::Image> _icon_image;
        std::optional<sf::Texture> _board_texture;
        std::optional<sf::Texture> _x_texture;
        std::optional<sf::Texture> _o_texture;
        std::optional<sf::Texture> _x_win_texture;
        std::optional<sf::Texture> _o_win_texture;
        std::optional<sf::Texture> _draw_texture;
        std::optional<sf::SoundBuffer> _win_sound;
        std::optional<sf::SoundBuffer> _click_sound;

        template <typename TResource>
        [[nodiscard]]
        static std::optional<TResource> load_resource(const std::filesystem::path &path)
        {
            TResource resource;

            if (!resource.loadFromFile(path))
            {
                return std::nullopt;
            }

            return resource;
        }

    public:
        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;
        Manager(Manager &&) = delete;
        Manager &operator=(Manager &&) = delete;

        Manager(const std::filesystem::path &directory)
        {
            _icon_image = load_resource<sf::Image>(directory / "images/icon.png");
            _board_texture = load_resource<sf::Texture>(directory / "images/board.png");
            _x_texture = load_resource<sf::Texture>(directory / "images/x.png");
            _o_texture = load_resource<sf::Texture>(directory / "images/o.png");
            _x_win_texture = load_resource<sf::Texture>(directory / "images/x_win.png");
            _o_win_texture = load_resource<sf::Texture>(directory / "images/o_win.png");
            _draw_texture = load_resource<sf::Texture>(directory / "images/draw.png");
            _win_sound = load_resource<sf::SoundBuffer>(directory / "audio/win.mp3");
            _click_sound = load_resource<sf::SoundBuffer>(directory / "audio/click.mp3");
        }

        [[nodiscard]]
        const sf::Image *get_icon() const noexcept
        {
            return _icon_image ? &*_icon_image : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *get_board() const noexcept
        {
            return _board_texture ? &*_board_texture : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *get_mark_texture(Cell cell) const noexcept
        {
            if (cell == Cell::X)
            {
                return _x_texture ? &*_x_texture : nullptr;
            }

            if (cell == Cell::O)
            {
                return _o_texture ? &*_o_texture : nullptr;
            }

            return nullptr;
        }

        [[nodiscard]]
        const sf::Texture *get_overlay_texture(GameResult result) const noexcept
        {
            if (result == GameResult::Draw)
            {
                return _draw_texture ? &*_draw_texture : nullptr;
            }

            if (result == GameResult::XWins)
            {
                return _x_win_texture ? &*_x_win_texture : nullptr;
            }

            if (result == GameResult::OWins)
            {
                return _o_win_texture ? &*_o_win_texture : nullptr;
            }

            return nullptr;
        }

        [[nodiscard]]
        const sf::SoundBuffer *get_click_sound() const noexcept
        {
            return _click_sound ? &*_click_sound : nullptr;
        }

        [[nodiscard]]
        const sf::SoundBuffer *get_win_sound() const noexcept
        {
            return _win_sound ? &*_win_sound : nullptr;
        }
    };
}
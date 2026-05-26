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
        std::optional<sf::Image> _icon;
        std::optional<sf::Texture> _board;
        std::optional<sf::Texture> _x;
        std::optional<sf::Texture> _o;
        std::optional<sf::Texture> _x_win;
        std::optional<sf::Texture> _o_win;
        std::optional<sf::Texture> _draw;
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
        Manager(const std::filesystem::path &directory)
        {
            _icon = load_resource<sf::Image>(directory / "icon.png");
            _board = load_resource<sf::Texture>(directory / "board.png");
            _x = load_resource<sf::Texture>(directory / "x.png");
            _o = load_resource<sf::Texture>(directory / "o.png");
            _x_win = load_resource<sf::Texture>(directory / "x_win.png");
            _o_win = load_resource<sf::Texture>(directory / "o_win.png");
            _draw = load_resource<sf::Texture>(directory / "draw.png");
            _win_sound = load_resource<sf::SoundBuffer>(directory / "win.mp3");
            _click_sound = load_resource<sf::SoundBuffer>(directory / "click.mp3");
        }

        [[nodiscard]]
        const sf::Image *icon() const noexcept
        {
            return _icon ? &*_icon : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *board() const noexcept
        {
            return _board ? &*_board : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *mark_texture(Cell cell) const noexcept
        {
            switch (cell)
            {
            case Cell::X:
            {
                return _x ? &*_x : nullptr;
            }
            case Cell::O:
            {
                return _o ? &*_o : nullptr;
            }
            default:
            {
                return nullptr;
            }
            }
        }

        [[nodiscard]]
        const sf::Texture *overlay_texture(GameResult result) const noexcept
        {
            switch (result)
            {
            case GameResult::XWins:
            {
                return _x_win ? &*_x_win : nullptr;
            }

            case GameResult::OWins:
            {
                return _o_win ? &*_o_win : nullptr;
            }

            case GameResult::Draw:
            {
                return _draw ? &*_draw : nullptr;
            }

            default:
            {
                return nullptr;
            }
            }
        }

        [[nodiscard]]
        const sf::SoundBuffer *click_sound() const noexcept
        {
            return _click_sound ? &*_click_sound : nullptr;
        }

        [[nodiscard]]
        const sf::SoundBuffer *win_sound() const noexcept
        {
            return _win_sound ? &*_win_sound : nullptr;
        }
    };
}
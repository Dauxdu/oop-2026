module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module Assets;

import GameLogic;

export namespace assets
{
    class Manager
    {
    private:
        sf::Texture _board;
        bool _has_board{};

        sf::Texture _x;
        bool _has_x{};
        sf::Texture _x_win;
        bool _has_x_win{};

        sf::Texture _o;
        bool _has_o{};
        sf::Texture _o_win;
        bool _has_o_win{};

        sf::Texture _draw;
        bool _has_draw{};

        sf::SoundBuffer _win_buffer;
        bool _has_win_sound{};
        sf::SoundBuffer _click_buffer;
        bool _has_click_sound{};

    public:
        Manager(const std::filesystem::path &dir)
        {
            _has_board = _board.loadFromFile((dir / "board.png"));

            _has_x = _x.loadFromFile((dir / "x.png"));
            _has_o = _o.loadFromFile((dir / "o.png"));

            _has_x_win = _x_win.loadFromFile((dir / "x_win.png"));
            _has_o_win = _o_win.loadFromFile((dir / "o_win.png"));
            _has_draw = _draw.loadFromFile((dir / "draw.png"));

            _has_win_sound = _win_buffer.loadFromFile((dir / "win.mp3"));
            _has_click_sound = _click_buffer.loadFromFile((dir / "click.mp3"));
        }

        [[nodiscard]]
        const sf::Texture *board() const noexcept
        {
            return _has_board ? &_board : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *mark_texture(Cell c) const noexcept
        {
            switch (c)
            {
            case Cell::X:
            {
                return _has_x ? &_x : nullptr;
            }

            case Cell::O:
            {
                return _has_o ? &_o : nullptr;
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
                return _has_x_win ? &_x_win : nullptr;
            }

            case GameResult::OWins:
            {
                return _has_o_win ? &_o_win : nullptr;
            }

            case GameResult::Draw:
            {
                return _has_draw ? &_draw : nullptr;
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
            return _has_click_sound ? &_click_buffer : nullptr;
        }

        [[nodiscard]]
        const sf::SoundBuffer *win_sound() const noexcept
        {
            return _has_win_sound ? &_win_buffer : nullptr;
        }
    };
}
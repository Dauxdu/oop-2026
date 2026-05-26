module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module Assets;

import std;
import GameLogic;

export namespace Assets
{
    class Manager
    {
        sf::Texture _board;
        sf::Texture _x;
        sf::Texture _o;

        sf::Texture _x_win;
        sf::Texture _o_win;
        sf::Texture _draw;

        sf::SoundBuffer _win_buffer;

        bool _has_board{};
        bool _has_x{};
        bool _has_o{};
        bool _has_x_win{};
        bool _has_o_win{};
        bool _has_draw{};
        bool _has_sound{};

        static bool load(sf::Texture &texture, const std::filesystem::path &path)
        {
            return texture.loadFromFile(path.string());
        }

    public:
        Manager(const std::filesystem::path &dir)
        {
            _has_board = load(_board, dir / "board.png");

            _has_x = load(_x, dir / "x.png");
            _has_o = load(_o, dir / "o.png");

            _has_x_win = load(_x_win, dir / "x_win.png");
            _has_o_win = load(_o_win, dir / "o_win.png");
            _has_draw = load(_draw, dir / "draw.png");

            _has_sound = _win_buffer.loadFromFile((dir / "win.mp3"));
        }

        [[nodiscard]]
        const sf::Texture *board() const noexcept
        {
            return _has_board ? &_board : nullptr;
        }

        [[nodiscard]]
        const sf::Texture *mark(Cell c) const noexcept
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
        const sf::Texture *overlay(GameResult result) const noexcept
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
        const sf::SoundBuffer *win_sound() const noexcept
        {
            return _has_sound ? &_win_buffer : nullptr;
        }
    };
}
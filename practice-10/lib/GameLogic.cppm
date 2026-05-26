export module GameLogic;

import std;

export enum class Cell : std::uint8_t {
    Empty = 0,
    X,
    O
};

export enum class GameResult : std::uint8_t {
    None,
    XWins,
    OWins,
    Draw
};

export namespace game_logic
{
    class Board
    {
    private:
        std::array<Cell, 3 * 3> _board{};
        Cell _current{Cell::X};
        GameResult _result{GameResult::None};

        [[nodiscard]]
        bool won(Cell p) const noexcept
        {
            for (int i = 0; i < 3; ++i)
            {
                if ((_board[i * 3 + 0] == p &&
                     _board[i * 3 + 1] == p &&
                     _board[i * 3 + 2] == p) ||
                    (_board[0 * 3 + i] == p &&
                     _board[1 * 3 + i] == p &&
                     _board[2 * 3 + i] == p))
                {
                    return true;
                }
            }

            return (_board[0] == p &&
                    _board[4] == p &&
                    _board[8] == p) ||
                   (_board[2] == p &&
                    _board[4] == p &&
                    _board[6] == p);
        }

        [[nodiscard]]
        bool full() const noexcept
        {
            return std::ranges::none_of(_board, [](Cell c)
                                        { return c == Cell::Empty; });
        }

        void update_game_state() noexcept
        {
            if (won(_current))
            {
                _result = _current == Cell::X ? GameResult::XWins : GameResult::OWins;

                return;
            }

            if (full())
            {
                _result = GameResult::Draw;

                return;
            }

            _current = _current == Cell::X ? Cell::O : Cell::X;
        }

    public:
        [[nodiscard]]
        bool move(int x, int y) noexcept
        {
            if (is_over() || x < 0 || x >= 3 || y < 0 || y >= 3)
            {
                return false;
            }

            Cell &cell = _board[y * 3 + x];
            if (cell != Cell::Empty)
            {
                return false;
            }
            cell = _current;

            update_game_state();

            return true;
        }

        [[nodiscard]]
        Cell get(int x, int y) const noexcept
        {
            return _board[y * 3 + x];
        }

        [[nodiscard]]
        GameResult result() const noexcept
        {
            return _result;
        }

        [[nodiscard]]
        bool is_over() const noexcept
        {
            return _result != GameResult::None;
        }

        void reset() noexcept
        {
            _board.fill(Cell::Empty);
            _current = Cell::X;
            _result = GameResult::None;
        }
    };
}
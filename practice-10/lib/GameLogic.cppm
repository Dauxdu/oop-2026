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

export namespace GameLogic
{
    constexpr int BOARD_SIZE = 3;

    class Logic
    {
        std::array<Cell, BOARD_SIZE * BOARD_SIZE> _board{};

        Cell _current{Cell::X};
        GameResult _result{GameResult::None};

        bool _over{false};

        [[nodiscard]]
        static constexpr Cell next_player(Cell c) noexcept
        {
            return c == Cell::X ? Cell::O : Cell::X;
        }

        [[nodiscard]]
        static constexpr bool valid(int x, int y) noexcept
        {
            return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
        }

        [[nodiscard]]
        static constexpr std::size_t index(int x, int y) noexcept
        {
            return static_cast<std::size_t>(y * BOARD_SIZE + x);
        }

        [[nodiscard]]
        constexpr bool line(Cell a, Cell b, Cell c, Cell p) const noexcept
        {
            return a == p && b == p && c == p;
        }

        [[nodiscard]]
        Cell at(int x, int y) const noexcept
        {
            return _board[index(x, y)];
        }

        [[nodiscard]]
        bool won(Cell p) const noexcept
        {
            for (int i = 0; i < BOARD_SIZE; ++i)
            {
                if (line(at(0, i), at(1, i), at(2, i), p) || line(at(i, 0), at(i, 1), at(i, 2), p))
                {
                    return true;
                }
            }

            return line(at(0, 0), at(1, 1), at(2, 2), p) || line(at(2, 0), at(1, 1), at(0, 2), p);
        }

        [[nodiscard]]
        bool full() const noexcept
        {
            return std::ranges::none_of(_board, [](Cell c)
                                        { return c == Cell::Empty; });
        }

        void update_state() noexcept
        {
            if (won(_current))
            {
                _result = _current == Cell::X ? GameResult::XWins : GameResult::OWins;

                _over = true;

                return;
            }

            if (full())
            {
                _result = GameResult::Draw;
                _over = true;

                return;
            }

            _current = next_player(_current);
        }

    public:
        [[nodiscard]]
        bool move(int x, int y) noexcept
        {
            if (_over || !valid(x, y))
            {
                return false;
            }

            auto &cell = _board[index(x, y)];

            if (cell != Cell::Empty)
            {
                return false;
            }

            cell = _current;

            update_state();

            return true;
        }

        [[nodiscard]]
        Cell get(int x, int y) const noexcept
        {
            return at(x, y);
        }

        [[nodiscard]]
        GameResult result() const noexcept
        {
            return _result;
        }

        [[nodiscard]]
        bool is_over() const noexcept
        {
            return _over;
        }

        void reset() noexcept
        {
            _board.fill(Cell::Empty);

            _current = Cell::X;
            _result = GameResult::None;
            _over = false;
        }
    };
}
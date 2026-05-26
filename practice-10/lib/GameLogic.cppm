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
    public:
        static constexpr int size = 3;

    private:
        std::array<Cell, size * size> _board{};
        Cell _current{Cell::X};
        GameResult _result{GameResult::None};

        static constexpr std::array win_lines{
            std::array{0, 1, 2},
            std::array{3, 4, 5},
            std::array{6, 7, 8},

            std::array{0, 3, 6},
            std::array{1, 4, 7},
            std::array{2, 5, 8},

            std::array{0, 4, 8},
            std::array{2, 4, 6},
        };

        [[nodiscard]]
        static bool is_valid_position(int x, int y) noexcept
        {
            return x >= 0 && x < size && y >= 0 && y < size;
        }

        [[nodiscard]]
        bool won(Cell player) const noexcept
        {
            for (const auto &line : win_lines)
            {
                if (_board[line[0]] == player && _board[line[1]] == player && _board[line[2]] == player)
                {
                    return true;
                }
            }

            return false;
        }

        [[nodiscard]]
        bool full() const noexcept
        {
            return std::ranges::none_of(_board, [](Cell cell)
                                        { return cell == Cell::Empty; });
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
            if (is_over() || !is_valid_position(x, y))
            {
                return false;
            }

            Cell &cell = _board[y * size + x];

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
            return _board[y * size + x];
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
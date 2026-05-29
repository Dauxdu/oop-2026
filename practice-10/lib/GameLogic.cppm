export module GameLogic;

import std;

export enum class Cell : std::uint8_t {
    Empty,
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
        Cell _current_player{Cell::X};
        GameResult _game_result{GameResult::None};
        std::array<Cell, size * size> _board{Cell::Empty};

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
        static bool is_valid_move(int x, int y) noexcept
        {
            return x >= 0 && x < size && y >= 0 && y < size;
        }

        [[nodiscard]]
        bool is_board_full() const noexcept
        {
            return std::ranges::none_of(_board, [](Cell cell)
                                        { return cell == Cell::Empty; });
        }

        [[nodiscard]]
        bool is_player_win(Cell player) const noexcept
        {
            for (const auto &line_index : win_lines)
            {
                if (_board[line_index[0]] == player && _board[line_index[1]] == player && _board[line_index[2]] == player)
                {
                    return true;
                }
            }

            return false;
        }

        void update_game_state() noexcept
        {
            if (is_player_win(_current_player))
            {
                _game_result = _current_player == Cell::X ? GameResult::XWins : GameResult::OWins;

                return;
            }

            if (is_board_full())
            {
                _game_result = GameResult::Draw;

                return;
            }

            _current_player = _current_player == Cell::X ? Cell::O : Cell::X;
        }

    public:
        [[nodiscard]]
        Cell get_cell(int x, int y) const noexcept
        {
            return _board[y * size + x];
        }

        [[nodiscard]]
        GameResult get_game_result() const noexcept
        {
            return _game_result;
        }

        bool is_game_over() const noexcept
        {
            return _game_result != GameResult::None;
        }

        [[nodiscard]]
        bool move_cell(int x, int y) noexcept
        {
            if (is_game_over() || !is_valid_move(x, y))
            {
                return false;
            }

            Cell &cell = _board[y * size + x];
            if (cell != Cell::Empty)
            {
                return false;
            }

            cell = _current_player;

            update_game_state();

            return true;
        }

        void reset() noexcept
        {
            _board.fill(Cell::Empty);

            _current_player = Cell::X;
            _game_result = GameResult::None;
        }
    };
}
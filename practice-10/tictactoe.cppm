module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module tictactoe;
import api;
import std;

export namespace tictactoe
{
    api::GamePtr make(float width, float height);
}

enum class Cell : uint8_t
{
    Empty = 0,
    X,
    O
};

enum class GameResult : uint8_t
{
    None,
    XWins,
    OWins,
    Draw
};

constexpr int BOARD_SIZE = 3;

class GameLogic
{
    std::array<Cell, BOARD_SIZE * BOARD_SIZE> _board{};
    Cell _current{Cell::X};
    GameResult _result{GameResult::None};
    bool _over{false};

    [[nodiscard]] Cell at(int x, int y) const noexcept
    {
        return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) ? _board[y * BOARD_SIZE + x] : Cell::Empty;
    }

    [[nodiscard]] bool line(Cell a, Cell b, Cell c, Cell p) const noexcept
    {
        return a == p && b == p && c == p;
    }

    [[nodiscard]] bool won(Cell p) const noexcept
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (line(at(0, i), at(1, i), at(2, i), p))
            {
                return true;
            }

            if (line(at(i, 0), at(i, 1), at(i, 2), p))
            {
                return true;
            }
        }

        return line(at(0, 0), at(1, 1), at(2, 2), p) || line(at(2, 0), at(1, 1), at(0, 2), p);
    }

    [[nodiscard]] bool full() const noexcept
    {
        return std::none_of(_board.begin(), _board.end(), [](Cell c)
                            { return c == Cell::Empty; });
    }

public:
    [[nodiscard]] bool move(int x, int y) noexcept
    {
        if (_over || x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        {
            return false;
        }

        auto &cell = _board[y * BOARD_SIZE + x];
        if (cell != Cell::Empty)
        {
            return false;
        }

        cell = _current;
        if (won(_current))
        {
            _result = (_current == Cell::X) ? GameResult::XWins : GameResult::OWins;
            _over = true;

            return true;
        }

        if (full())
        {
            _result = GameResult::Draw;
            _over = true;

            return true;
        }

        _current = (_current == Cell::X) ? Cell::O : Cell::X;

        return true;
    }

    [[nodiscard]] Cell get(int x, int y) const noexcept
    {
        return at(x, y);
    }

    [[nodiscard]] GameResult result() const noexcept
    {
        return _result;
    }

    [[nodiscard]] bool is_over() const noexcept
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

class AssetLoader
{
    struct Assets
    {
        std::optional<sf::Texture> board, x, o, x_win, o_win, draw_win;
        std::optional<sf::SoundBuffer> win_sound;
    } _assets;

    static std::optional<sf::Texture> load_tex(const std::filesystem::path &p)
    {
        sf::Texture t;
        return t.loadFromFile(p.string()) ? std::optional{t} : std::nullopt;
    }

    static std::optional<sf::SoundBuffer> load_snd(const std::filesystem::path &p)
    {
        sf::SoundBuffer b;
        return b.loadFromFile(p.string()) ? std::optional{b} : std::nullopt;
    }

public:
    explicit AssetLoader(const std::filesystem::path &dir)
    {
        _assets.board = load_tex(dir / "board.png");
        _assets.x = load_tex(dir / "x.png");
        _assets.o = load_tex(dir / "o.png");
        _assets.x_win = load_tex(dir / "x_win.png");
        _assets.o_win = load_tex(dir / "o_win.png");
        _assets.draw_win = load_tex(dir / "draw_win.png");

        for (const char *ext : {".mp3", ".wav", ".ogg"})
        {
            if (auto s = load_snd(dir / ("win" + std::string{ext})))
            {
                _assets.win_sound = std::move(s);
                break;
            }
        }
    }

    [[nodiscard]] const sf::Texture *board() const noexcept
    {
        return _assets.board.has_value() ? &_assets.board.value() : nullptr;
    }

    [[nodiscard]] const sf::Texture *x_mark() const noexcept
    {
        return _assets.x.has_value() ? &_assets.x.value() : nullptr;
    }

    [[nodiscard]] const sf::Texture *o_mark() const noexcept
    {
        return _assets.o.has_value() ? &_assets.o.value() : nullptr;
    }

    [[nodiscard]] const sf::Texture *win_overlay(GameResult r) const noexcept
    {
        switch (r)
        {
        case GameResult::XWins:
        {
            return _assets.x_win.has_value() ? &_assets.x_win.value() : nullptr;
        }

        case GameResult::OWins:
        {
            return _assets.o_win.has_value() ? &_assets.o_win.value() : nullptr;
        }

        case GameResult::Draw:
        {
            return _assets.draw_win.has_value() ? &_assets.draw_win.value() : nullptr;
        }

        default:
            return nullptr;
        }
    }

    [[nodiscard]] std::unique_ptr<sf::Sound> make_win_sound() const
    {
        if (!_assets.win_sound)
        {
            return nullptr;
        }
        auto s = std::make_unique<sf::Sound>(*_assets.win_sound);
        s->setVolume(60.f);

        return s;
    }

    [[nodiscard]] bool has_board() const noexcept
    {
        return _assets.board.has_value();
    }
};

class Renderer
{
    const AssetLoader &_assets;
    float _w{}, _h{};

    [[nodiscard]] float cw() const noexcept
    {
        return _w / BOARD_SIZE;
    }

    [[nodiscard]] float ch() const noexcept
    {
        return _h / BOARD_SIZE;
    }

    void draw_grid_fallback(sf::RenderTarget &t) const
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color{200, 200, 200});

        for (int i = 1; i < BOARD_SIZE; ++i)
        {
            line.setSize({2.f, _h});
            line.setPosition({i * cw() - 1.f, 0.f});
            t.draw(line);

            line.setSize({_w, 2.f});
            line.setPosition({0.f, i * ch() - 1.f});
            t.draw(line);
        }
    }

public:
    Renderer(float w, float h, const AssetLoader &assets) : _w{w}, _h{h}, _assets{assets} {}

    void render(sf::RenderTarget &target, const GameLogic &game) const
    {
        // Фон / поле — используем сохранённую текстуру напрямую
        if (const auto *board_tex = _assets.board())
        {
            sf::Sprite board{*board_tex};
            board.setScale({_w / static_cast<float>(board_tex->getSize().x), _h / static_cast<float>(board_tex->getSize().y)});
            target.draw(board);
        }
        else
        {
            target.clear(sf::Color{30, 30, 40});
            draw_grid_fallback(target);
        }

        const auto *xt = _assets.x_mark();
        const auto *ot = _assets.o_mark();

        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            for (int x = 0; x < BOARD_SIZE; ++x)
            {
                float px = x * cw(), py = y * ch();
                sf::Vector2f center{px + cw() / 2.f, py + ch() / 2.f};

                if (game.get(x, y) == Cell::X && xt)
                {
                    sf::Sprite s{*xt};
                    float scale = (std::min(cw(), ch()) * 0.8f) / std::max(static_cast<float>(xt->getSize().x),
                                                                           static_cast<float>(xt->getSize().y));
                    s.setScale({scale, scale});
                    s.setOrigin(s.getLocalBounds().getCenter());
                    s.setPosition(center);
                    target.draw(s);
                }
                else if (game.get(x, y) == Cell::O && ot)
                {
                    sf::Sprite s{*ot};
                    float scale = (std::min(cw(), ch()) * 0.8f) /
                                  std::max(static_cast<float>(ot->getSize().x),
                                           static_cast<float>(ot->getSize().y));
                    s.setScale({scale, scale});
                    s.setOrigin(s.getLocalBounds().getCenter());
                    s.setPosition(center);
                    target.draw(s);
                }
            }
        }

        // Оверлей победы/ничьей
        if (game.is_over())
        {
            if (const auto *overlay = _assets.win_overlay(game.result()))
            {
                sf::Sprite win{*overlay};
                win.setScale({_w / static_cast<float>(overlay->getSize().x),
                              _h / static_cast<float>(overlay->getSize().y)});
                target.draw(win);
            }
        }
    }

    [[nodiscard]] float cell_width() const noexcept
    {
        return cw();
    }

    [[nodiscard]] float cell_height() const noexcept
    {
        return ch();
    }
};

class TicTacToe final : public api::IGame
{
    GameLogic _logic;
    AssetLoader _assets;
    Renderer _renderer;
    std::unique_ptr<sf::Sound> _win_sound;

public:
    TicTacToe(float width, float height) : _assets{std::filesystem::current_path() / "assets"}, _renderer{width, height, _assets}
    {
        _win_sound = _assets.make_win_sound();
    }

    void update(float) override {}

    void handle_event(const sf::Event &event) override
    {
        if (const auto *mb = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mb->button == sf::Mouse::Button::Left && !_logic.is_over())
            {
                int x = static_cast<int>(mb->position.x / _renderer.cell_width());
                int y = static_cast<int>(mb->position.y / _renderer.cell_height());

                if (_logic.move(x, y) && _logic.is_over() && _win_sound)
                {
                    _win_sound->play();
                }
            }
        }
    }

    void draw(sf::RenderTarget &target) const override
    {
        _renderer.render(target, _logic);
    }
};

namespace tictactoe
{
    api::GamePtr make(float width, float height)
    {
        return std::make_unique<TicTacToe>(width, height);
    }
}
module;

#include <SFML/Graphics.hpp>

export module API;

import std;
export namespace api
{
    class IGame
    {
    protected:
        IGame() = default;
        IGame(const IGame &) = default;
        IGame &operator=(const IGame &) = default;

    public:
        virtual ~IGame() = default;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderTarget &) const = 0;
        virtual void handle_event(const sf::Event &) = 0;
    };

    using GamePtr = std::unique_ptr<IGame>;
}
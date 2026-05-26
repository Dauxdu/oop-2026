module;

#include <SFML/Graphics.hpp>

export module API;

export namespace api
{
    class IDrawable
    {
    protected:
        IDrawable() = default;
        IDrawable(const IDrawable &) = default;
        IDrawable &operator=(const IDrawable &) = default;

    public:
        virtual ~IDrawable() = default;
        virtual void draw(sf::RenderTarget &target) const = 0;
    };

    class IUpdatable
    {
    protected:
        IUpdatable() = default;
        IUpdatable(const IUpdatable &) = default;
        IUpdatable &operator=(const IUpdatable &) = default;

    public:
        virtual ~IUpdatable() = default;
        virtual void update(float dt) = 0;
    };

    class IEventHandler
    {
    protected:
        IEventHandler() = default;
        IEventHandler(const IEventHandler &) = default;
        IEventHandler &operator=(const IEventHandler &) = default;

    public:
        virtual ~IEventHandler() = default;
        virtual void handle_event(const sf::Event &event) = 0;
    };
}
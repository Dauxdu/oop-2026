#include <SFML/Graphics.hpp>

import std;
import api;
import spiral;

static sf::String make_string(const std::string_view s)
{
  return sf::String::fromUtf8(s.begin(), s.end());
}

struct WindowConfig final
{
  std::filesystem::path icon_path{"assets/icon.png"};
  sf::String title{make_string("Демо")};
  std::uint32_t style{sf::Style::Titlebar | sf::Style::Close /* | sf::Style::Resize */};
  sf::Vector2u size{1920, 1080};
};

struct Config final
{
  WindowConfig window;
  spiral::Config spiral{
      static_cast<float>(window.size.x),
      static_cast<float>(window.size.y)};
};

int main()
{
  const Config cfg;

  sf::RenderWindow w{
      sf::VideoMode(cfg.window.size),
      cfg.window.title,
      cfg.window.style};
  w.setIcon(sf::Image(cfg.window.icon_path));
  w.setVerticalSyncEnabled(true);

  sf::Clock clock;

  api::Scene scene;
  scene.drawables.push_back(spiral::make(cfg.spiral));

  while (w.isOpen())
  {
    while (const auto e = w.pollEvent())
    {
      if (e->is<sf::Event::Closed>())
      {
        w.close();
        break;
      }
    }

    w.clear(sf::Color::White);

    scene.update(clock.getElapsedTime().asSeconds());
    scene.draw(static_cast<sf::RenderTarget *>(&w));

    w.display();
  }
}

module;

#include <SFML/Graphics.hpp>

module spiral;

using namespace spiral;

struct Point
{
  float t0{0};
  float growth_factor{0};
  float angular_speed{0};
};

class Spiral : public api::Drawable, public api::Updatable
{
private:
  std::default_random_engine _e;
  std::uniform_real_distribution<float> _growth_factor_dist;
  std::uniform_real_distribution<float> _angular_speed_dist;
  std::uniform_int_distribution<int> _color_dist{0, 255};
  float _width{0};
  float _height{0};
  std::vector<Point> _points;
  sf::VertexArray _vertices;

  void reset_point(Point &p, sf::Vertex &v, const float t)
  {
    p.t0 = t;
    p.growth_factor = _growth_factor_dist(_e);
    p.angular_speed = _angular_speed_dist(_e);

    v.color = sf::Color{
        static_cast<std::uint8_t>(_color_dist(_e)),
        static_cast<std::uint8_t>(_color_dist(_e)),
        static_cast<std::uint8_t>(_color_dist(_e))};
  }

public:
  Spiral(const Config &cfg) : _growth_factor_dist{cfg.growth_factor_min, cfg.growth_factor_max},
                              _angular_speed_dist{cfg.angular_speed_min, cfg.angular_speed_max},
                              _width{cfg.width},
                              _height{cfg.height},
                              _points{cfg.n},
                              _vertices{sf::PrimitiveType::Points, cfg.n}
  {
    for (std::size_t i = 0; i < cfg.n; ++i)
    {
      reset_point(_points[i], _vertices[i], 0);
    }
  }

  void update(const float t) override
  {
    const sf::Vector2f center{_width / 2, _height / 2};

    for (std::size_t i = 0; i < _points.size(); ++i)
    {
      Point &p = _points[i];
      const float theta = p.angular_speed * (t - p.t0);
      const float r = std::pow(std::numbers::e_v<float>, p.growth_factor * theta);
      const float x = center.x + r * std::cos(theta);
      const float y = center.y + r * std::sin(theta);

      _vertices[i].position = {x, y};

      if ((x < 0 || x >= _width) && (y < 0 || y >= _height))
      {
        reset_point(p, _vertices[i], t);
      }
    }
  }

  void draw(std::any render_target) const override
  {
    std::any_cast<sf::RenderTarget *>(render_target)->draw(_vertices);
  }
};

api::DrawablePtr spiral::make(const Config &cfg)
{
  return std::make_shared<Spiral>(cfg);
}

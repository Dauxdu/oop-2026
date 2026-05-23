export module spiral;

import std;
import api;

export namespace spiral
{

  struct Config final
  {
    float width{0};
    float height{0};

    std::size_t n{100'000};

    float growth_factor_min{0.10f};
    float growth_factor_max{0.11f};

    float angular_speed_min{1 * std::numbers::pi_v<float> / 2};
    float angular_speed_max{4 * std::numbers::pi_v<float> / 2};

    Config(float width, float height) : width{width}, height{height} {}
  };

  api::DrawablePtr make(const Config &cfg);

}

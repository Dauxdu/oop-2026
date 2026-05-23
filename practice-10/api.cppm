export module api;

import std;

export namespace api
{

  class Drawable
  {
  public:
    virtual void draw(std::any render_target) const = 0;

    virtual ~Drawable() = default;

  protected:
    Drawable() = default;
    Drawable(const Drawable &) = default;
    Drawable &operator=(const Drawable &) = default;
  };

  using DrawablePtr = std::shared_ptr<Drawable>;

  class Updatable
  {
  public:
    virtual void update(float t) = 0;

    virtual ~Updatable() = default;

  protected:
    Updatable() = default;
    Updatable(const Updatable &) = default;
    Updatable &operator=(const Updatable &) = default;
  };

  struct Scene final : public Drawable, public Updatable
  {
    std::vector<DrawablePtr> drawables;

    void update(float t) override
    {
      for (auto &drawable : drawables)
      {
        if (auto updatable = dynamic_cast<Updatable *>(drawable.get()))
        {
          updatable->update(t);
        }
      }
    }

    void draw(std::any render_target) const override
    {
      for (auto &drawable : drawables)
      {
        drawable->draw(render_target);
      }
    }
  };

}

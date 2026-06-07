module;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

export module Assets;

import std;

export namespace assets
{
    enum class ImageID
    {
        Icon
    };

    enum class TextureID
    {
        Board,
        X,
        O,
        XWin,
        OWin,
        Draw
    };

    enum class SoundID
    {
        Win,
        Click
    };

    class Manager final
    {
    private:
        std::array<sf::Image, 1> _images;
        std::array<sf::Texture, 6> _textures;
        std::array<sf::SoundBuffer, 2> _sounds;

        template <typename TResource>
        TResource load_resource(const std::filesystem::path &filepath) const
        {
            TResource resource;
            if (!resource.loadFromFile(filepath))
            {
                throw std::runtime_error("Failed to load resource: " + filepath.string());
            }
            return resource;
        }

    public:
        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;
        Manager(Manager &&) = delete;
        Manager &operator=(Manager &&) = delete;

        explicit Manager(const std::filesystem::path &directory)
        {
            _images[0] = load_resource<sf::Image>(directory / "image/icon.png");
            _textures[0] = load_resource<sf::Texture>(directory / "texture/board.png");
            _textures[1] = load_resource<sf::Texture>(directory / "texture/x.png");
            _textures[2] = load_resource<sf::Texture>(directory / "texture/o.png");
            _textures[3] = load_resource<sf::Texture>(directory / "texture/x_win.png");
            _textures[4] = load_resource<sf::Texture>(directory / "texture/o_win.png");
            _textures[5] = load_resource<sf::Texture>(directory / "texture/draw.png");
            _sounds[0] = load_resource<sf::SoundBuffer>(directory / "sfx/win.ogg");
            _sounds[1] = load_resource<sf::SoundBuffer>(directory / "sfx/click.ogg");
        }

        [[nodiscard]] const sf::Image &get_image(const ImageID id) const noexcept
        {
            return _images[static_cast<std::size_t>(id)];
        }

        [[nodiscard]] const sf::Texture &get_texture(const TextureID id) const noexcept
        {
            return _textures[static_cast<std::size_t>(id)];
        }

        [[nodiscard]] const sf::SoundBuffer &get_sound(const SoundID id) const noexcept
        {
            return _sounds[static_cast<std::size_t>(id)];
        }
    };
}
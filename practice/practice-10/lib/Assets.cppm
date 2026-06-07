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
            _images[static_cast<std::size_t>(ImageID::Icon)] = load_resource<sf::Image>(directory / "image/icon.png");
            _textures[static_cast<std::size_t>(TextureID::Board)] = load_resource<sf::Texture>(directory / "texture/board.png");
            _textures[static_cast<std::size_t>(TextureID::X)] = load_resource<sf::Texture>(directory / "texture/x.png");
            _textures[static_cast<std::size_t>(TextureID::O)] = load_resource<sf::Texture>(directory / "texture/o.png");
            _textures[static_cast<std::size_t>(TextureID::XWin)] = load_resource<sf::Texture>(directory / "texture/x_win.png");
            _textures[static_cast<std::size_t>(TextureID::OWin)] = load_resource<sf::Texture>(directory / "texture/o_win.png");
            _textures[static_cast<std::size_t>(TextureID::Draw)] = load_resource<sf::Texture>(directory / "texture/draw.png");
            _sounds[static_cast<std::size_t>(SoundID::Win)] = load_resource<sf::SoundBuffer>(directory / "sfx/win.ogg");
            _sounds[static_cast<std::size_t>(SoundID::Click)] = load_resource<sf::SoundBuffer>(directory / "sfx/click.ogg");
        }

        [[nodiscard]] const sf::Image &get_image(const ImageID id) const
        {
            return _images[static_cast<std::size_t>(id)];
        }

        [[nodiscard]] const sf::Texture &get_texture(const TextureID id) const
        {
            return _textures[static_cast<std::size_t>(id)];
        }

        [[nodiscard]] const sf::SoundBuffer &get_sound(const SoundID id) const
        {
            return _sounds[static_cast<std::size_t>(id)];
        }
    };
}
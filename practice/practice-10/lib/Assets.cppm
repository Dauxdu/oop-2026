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
        Click,
        Draw
    };

    class Manager final
    {
    private:
        std::unordered_map<ImageID, sf::Image> _images;
        std::unordered_map<TextureID, sf::Texture> _textures;
        std::unordered_map<SoundID, sf::SoundBuffer> _sounds;

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
            _images[ImageID::Icon] = load_resource<sf::Image>(directory / "image/icon.png");
            _textures[TextureID::Board] = load_resource<sf::Texture>(directory / "texture/board.png");
            _textures[TextureID::X] = load_resource<sf::Texture>(directory / "texture/x.png");
            _textures[TextureID::O] = load_resource<sf::Texture>(directory / "texture/o.png");
            _textures[TextureID::XWin] = load_resource<sf::Texture>(directory / "texture/x_win.png");
            _textures[TextureID::OWin] = load_resource<sf::Texture>(directory / "texture/o_win.png");
            _textures[TextureID::Draw] = load_resource<sf::Texture>(directory / "texture/draw.png");
            _sounds[SoundID::Win] = load_resource<sf::SoundBuffer>(directory / "sfx/win.ogg");
            _sounds[SoundID::Click] = load_resource<sf::SoundBuffer>(directory / "sfx/click.ogg");
            _sounds[SoundID::Draw] = load_resource<sf::SoundBuffer>(directory / "sfx/draw.ogg");
        }

        [[nodiscard]] const sf::Image &get_image(const ImageID id) const
        {
            return _images.at(id);
        }

        [[nodiscard]] const sf::Texture &get_texture(const TextureID id) const
        {
            return _textures.at(id);
        }

        [[nodiscard]] const sf::SoundBuffer &get_sound(const SoundID id) const
        {
            return _sounds.at(id);
        }
    };
}

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
        std::unordered_map<ImageID, sf::Image> _images;
        std::unordered_map<TextureID, sf::Texture> _textures;
        std::unordered_map<SoundID, sf::SoundBuffer> _sounds;

        template <typename TResource>
        TResource load_resource(const std::filesystem::path &directory, const std::string &filename) const
        {
            TResource resource;
            const auto filepath = directory / filename;
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
            _images.emplace(ImageID::Icon, load_resource<sf::Image>(directory, "image/icon.png"));
            _textures.emplace(TextureID::Board, load_resource<sf::Texture>(directory, "texture/board.png"));
            _textures.emplace(TextureID::X, load_resource<sf::Texture>(directory, "texture/x.png"));
            _textures.emplace(TextureID::XWin, load_resource<sf::Texture>(directory, "texture/x_win.png"));
            _textures.emplace(TextureID::O, load_resource<sf::Texture>(directory, "texture/o.png"));
            _textures.emplace(TextureID::OWin, load_resource<sf::Texture>(directory, "texture/o_win.png"));
            _textures.emplace(TextureID::Draw, load_resource<sf::Texture>(directory, "texture/draw.png"));
            _sounds.emplace(SoundID::Win, load_resource<sf::SoundBuffer>(directory, "sfx/win.ogg"));
            _sounds.emplace(SoundID::Click, load_resource<sf::SoundBuffer>(directory, "sfx/click.ogg"));
        }

        [[nodiscard]]
        const sf::Image &get_image(ImageID id) const
        {
            auto it = _images.find(id);
            if (it == _images.end())
            {
                throw std::runtime_error(std::format("Image not found: {}", std::to_underlying(id)));
            }

            return it->second;
        }

        [[nodiscard]]
        const sf::Texture &get_texture(TextureID id) const
        {
            auto it = _textures.find(id);
            if (it == _textures.end())
            {
                throw std::runtime_error(std::format("Texture not found: {}", std::to_underlying(id)));
            }

            return it->second;
        }

        [[nodiscard]]
        const sf::SoundBuffer &get_sound(SoundID id) const
        {
            auto it = _sounds.find(id);
            if (it == _sounds.end())
            {
                throw std::runtime_error(std::format("Sound not found: {}", std::to_underlying(id)));
            }

            return it->second;
        }
    };
}
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

    class Manager
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

            if constexpr (std::is_same_v<TResource, sf::Image>)
            {
                if (!resource.loadFromFile(filepath))
                {
                    throw std::runtime_error("Failed to load image: " + filepath.string());
                }
            }
            else if constexpr (std::is_same_v<TResource, sf::Texture>)
            {
                if (!resource.loadFromFile(filepath))

                {
                    throw std::runtime_error("Failed to load texture: " + filepath.string());
                }
            }
            else if constexpr (std::is_same_v<TResource, sf::SoundBuffer>)
            {
                if (!resource.loadFromFile(filepath))
                {
                    throw std::runtime_error("Failed to load sound: " + filepath.string());
                }
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
            _images[ImageID::Icon] = load_resource<sf::Image>(directory, "image/icon.png");
            _textures[TextureID::Board] = load_resource<sf::Texture>(directory, "texture/board.png");
            _textures[TextureID::X] = load_resource<sf::Texture>(directory, "texture/x.png");
            _textures[TextureID::XWin] = load_resource<sf::Texture>(directory, "texture/x_win.png");
            _textures[TextureID::O] = load_resource<sf::Texture>(directory, "texture/o.png");
            _textures[TextureID::OWin] = load_resource<sf::Texture>(directory, "texture/o_win.png");
            _textures[TextureID::Draw] = load_resource<sf::Texture>(directory, "texture/draw.png");
            _sounds[SoundID::Win] = load_resource<sf::SoundBuffer>(directory, "sfx/win.ogg");
            _sounds[SoundID::Click] = load_resource<sf::SoundBuffer>(directory, "sfx/click.ogg");
        }

        [[nodiscard]]
        const sf::Image &get_image(ImageID id) const
        {
            auto it = _images.find(id);
            if (it == _images.end())
            {
                throw std::runtime_error(std::format("Asset not found: ImageID {}", std::to_underlying(id)));
            }

            return it->second;
        }

        [[nodiscard]]
        const sf::Texture &get_texture(TextureID id) const
        {
            auto it = _textures.find(id);
            if (it == _textures.end())
            {
                throw std::runtime_error(std::format("Asset not found: TextureID {}", std::to_underlying(id)));
            }

            return it->second;
        }

        [[nodiscard]]
        const sf::SoundBuffer &get_sound(SoundID id) const
        {
            auto it = _sounds.find(id);
            if (it == _sounds.end())
            {
                throw std::runtime_error(std::format("Asset not found: SoundID {}", std::to_underlying(id)));
            }

            return it->second;
        }
    };
}
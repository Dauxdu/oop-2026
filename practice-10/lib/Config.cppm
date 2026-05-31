module;

#include <nlohmann/json.hpp>

export module Config;

import std;

export namespace config
{
    struct Window
    {
        unsigned int width{800};
        unsigned int height{800};
        unsigned int fps{60};
        bool vsync{true};
    };

    struct Audio
    {
        float master_volume{100.f};
        float music_volume{100.f};
        float sfx_volume{100.f};
        bool mute{false};
    };

    class Manager
    {
        Window _window;
        Audio _audio;

    public:
        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;
        Manager(Manager &&) = delete;
        Manager &operator=(Manager &&) = delete;

        explicit Manager(const std::string &filename = "config.json")
        {
            try
            {
                std::ifstream file{filename};
                if (!file.is_open())
                {
                    std::println("Cannot open config: {}", filename);
                    return;
                }

                auto json = nlohmann::json::parse(file);
                if (json.contains("window"))
                {
                    const auto &w = json["window"];
                    _window.width = w.value("width", _window.width);
                    _window.height = w.value("height", _window.height);
                    _window.fps = w.value("fps", _window.fps);
                    _window.vsync = w.value("vsync", _window.vsync);
                }

                if (json.contains("audio"))
                {
                    const auto &a = json["audio"];
                    _audio.master_volume = a.value("master_volume", _audio.master_volume);
                    _audio.music_volume = a.value("music_volume", _audio.music_volume);
                    _audio.sfx_volume = a.value("sfx_volume", _audio.sfx_volume);
                    _audio.mute = a.value("mute", _audio.mute);
                }
            }
            catch (const std::exception &)
            {
                std::println("Failed to load config");
            }
        }

        [[nodiscard]] constexpr const Window &window() const noexcept
        {
            return _window;
        }

        [[nodiscard]] constexpr const Audio &audio() const noexcept
        {
            return _audio;
        }
    };
}
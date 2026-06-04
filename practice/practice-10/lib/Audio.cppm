module;

#include <SFML/Audio.hpp>

export module Audio;

import std;
import Assets;

export namespace audio
{
    class Manager final
    {
    private:
        const assets::Manager &_assets;
        std::optional<sf::Sound> _click_sound;
        std::optional<sf::Sound> _win_sound;
        bool _muted{false};

        void init_sounds(float sfx_volume) noexcept
        {
            try
            {
                _click_sound.emplace(_assets.get_sound(assets::SoundID::Click));
                _click_sound->setVolume(sfx_volume);
            }
            catch (const std::exception &e)
            {
                std::println("Failed to load click sound: {}", e.what());
            }

            try
            {
                _win_sound.emplace(_assets.get_sound(assets::SoundID::Win));
                _win_sound->setVolume(sfx_volume);
            }
            catch (const std::exception &e)
            {
                std::println("Failed to load win sound: {}", e.what());
            }
        }

    public:
        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;
        Manager(Manager &&) = delete;
        Manager &operator=(Manager &&) = delete;

        explicit Manager(const assets::Manager &assets, float sfx_volume) : _assets{assets}
        {
            init_sounds(sfx_volume);
        }

        void set_muted(bool muted) noexcept { _muted = muted; }
        void toggle_mute() noexcept { _muted = !_muted; }

        void set_sfx_volume(float volume) noexcept
        {
            const float clamped = std::clamp(volume, 0.f, 100.f);
            if (_click_sound)
            {
                _click_sound->setVolume(clamped);
            }

            if (_win_sound)
            {
                _win_sound->setVolume(clamped);
            }
        }

        void set_audio_levels(float master, float sfx) noexcept
        {
            const float master_clamped = std::clamp(master, 0.f, 100.f);
            const float sfx_clamped = std::clamp(sfx, 0.f, 100.f);
            set_sfx_volume((master_clamped * sfx_clamped) / 100.f);
        }

        void play_click() noexcept
        {
            if (!_muted && _click_sound)
            {
                _click_sound->play();
            }
        }

        void play_win() noexcept
        {
            if (!_muted && _win_sound)
            {
                _win_sound->play();
            }
        }
    };
}
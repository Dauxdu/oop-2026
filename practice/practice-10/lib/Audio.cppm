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

    public:
        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;
        Manager(Manager &&) = delete;
        Manager &operator=(Manager &&) = delete;

        explicit Manager(const assets::Manager &assets) : _assets{assets}
        {
            _click_sound.emplace(_assets.get_sound(assets::SoundID::Click));
            _win_sound.emplace(_assets.get_sound(assets::SoundID::Win));
        }

        void set_muted(bool muted) noexcept { _muted = muted; }

        void set_sfx_volume(const float volume) noexcept
        {
            const float clamped = std::clamp(volume, 0.f, 100.f);

            _click_sound->setVolume(clamped);
            _win_sound->setVolume(clamped);
        }

        void set_audio_levels(const float master, const float sfx) noexcept
        {
            const float master_clamped = std::clamp(master, 0.f, 100.f);
            const float sfx_clamped = std::clamp(sfx, 0.f, 100.f);
            set_sfx_volume((master_clamped * sfx_clamped) / 100.f);
        }

        void toggle_mute() noexcept { _muted = !_muted; }

        void play_click() noexcept
        {
            if (!_muted)
            {
                _click_sound->play();
            }
        }

        void play_win() noexcept
        {
            if (!_muted)
            {
                _win_sound->play();
            }
        }
    };
}
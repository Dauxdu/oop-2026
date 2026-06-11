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
        std::unordered_map<assets::SoundID, sf::Sound> _sounds;
        float _sfx_volume{100.f};
        bool _muted{false};

    public:
        explicit Manager(const assets::Manager &assets) : _assets{assets} {}

        void set_muted(const bool muted) noexcept { _muted = muted; }

        void set_sfx_volume(const float volume) noexcept
        {
            _sfx_volume = std::clamp(volume, 0.f, 100.f);
            for (auto &[id, sound] : _sounds)
            {
                sound.setVolume(_sfx_volume);
            }
        }

        void set_audio_levels(const float master, const float sfx) noexcept
        {
            const float master_clamped = std::clamp(master, 0.f, 100.f);
            const float sfx_clamped = std::clamp(sfx, 0.f, 100.f);
            set_sfx_volume((master_clamped * sfx_clamped) / 100.f);
        }

        void toggle_mute() noexcept { _muted = !_muted; }

        void play(const assets::SoundID id) noexcept
        {
            if (!_muted)
            {
                auto [it, inserted] = _sounds.try_emplace(id, _assets.get_sound(id));

                if (inserted)
                {
                    it->second.setVolume(_sfx_volume);
                }

                it->second.play();
            }
        }
    };
}
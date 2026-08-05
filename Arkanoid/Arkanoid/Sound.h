#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace ArkanoidGame
{
    class Sound
    {
    public:
        bool LoadSounds(const std::string& resourcesPath);
        void PlayEat();
        void PlayDeath();

        void SetSoundVolume(float volume);
        void SetMusicVolume(float volume);
        float GetSoundVolume() const { return soundVolume; }
        float GetMusicVolume() const { return musicVolume; }

        void IncreaseSoundVolume();
        void DecreaseSoundVolume();
        void IncreaseMusicVolume();
        void DecreaseMusicVolume();

        void PlayMusic();
        void StopMusic();

    private:
        sf::SoundBuffer eatBuffer;
        sf::Sound eatSound;
        sf::SoundBuffer deathBuffer;
        sf::Sound deathSound;
        sf::Music music;

        float soundVolume = 50.f;
        float musicVolume = 50.f;
    };


}
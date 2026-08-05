#include "Sound.h"
#include <cassert>

namespace ArkanoidGame
{
    bool Sound::LoadSounds(const std::string& resourcesPath)
    {
        if (!eatBuffer.loadFromFile(resourcesPath + "AppleEat.wav")) return false;
        eatSound.setBuffer(eatBuffer);

        if (!deathBuffer.loadFromFile(resourcesPath + "Death.wav")) return false;
        deathSound.setBuffer(deathBuffer);

        if (!music.openFromFile(resourcesPath + "Music.mp3")) return false;
        music.setLoop(true);
        music.setVolume(musicVolume);

        return true;
    }

    void Sound::PlayEat() { eatSound.play(); }
    void Sound::PlayDeath() { deathSound.play(); }

    void Sound::SetSoundVolume(float volume)
    {
        soundVolume = volume;
        eatSound.setVolume(soundVolume);
        deathSound.setVolume(soundVolume);
    }

    void Sound::SetMusicVolume(float volume)
    {
        musicVolume = volume;
        music.setVolume(musicVolume);
    }


    void Sound::PlayMusic() { music.play(); }
    void Sound::StopMusic() { music.stop(); }

    void Sound::IncreaseSoundVolume()
    {
        soundVolume = std::min(soundVolume + 10.f, 100.f);
        eatSound.setVolume(soundVolume);
        deathSound.setVolume(soundVolume);
    }

    void Sound::DecreaseSoundVolume()
    {
        soundVolume = std::max(soundVolume - 10.f, 0.f);
        eatSound.setVolume(soundVolume);
        deathSound.setVolume(soundVolume);
    }

    void Sound::IncreaseMusicVolume()
    {
        musicVolume = std::min(musicVolume + 10.f, 100.f);
        music.setVolume(musicVolume);
    }

    void Sound::DecreaseMusicVolume()
    {
        musicVolume = std::max(musicVolume - 10.f, 0.f);
        music.setVolume(musicVolume);
    }

}
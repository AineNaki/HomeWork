#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Stones.h"
#include <SFML/Audio.hpp>
#include "UI.h"
#include <map>
#include <string>

namespace ApplesGame
{
    enum class GameStatus // I separate the game state in this way
    {
        Playing,
        GameOver,
        Win
    };

    struct Game
    {
        Player player;
        Stone stones[NUM_STONES];


        Apple* applesDynamic = nullptr;
        int applesCount = 0;
        int applesGoal = 0;
        bool* applesEaten = nullptr;

        bool isInMainMenu = true;
        uint32_t modeFlags = 0;

        GameStatus status = GameStatus::Playing;
        int numEatenApples = 0;
        sf::RectangleShape background;

        sf::Clock gameClock;
        float lastTime = 0.f;

        sf::Font font;        
        UI ui;
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture stoneTexture;

        sf::SoundBuffer eatSoundBuffer;
        sf::Sound eatSound;

        sf::SoundBuffer stoneHitSoundBuffer;
        sf::Sound stoneHitSound;

        std::map<std::string, int> leaderboard;

    };

    void RestartGame(Game& game);
    void InitGame(Game& game);
    void ApplyGameMode(Game& game);
    void CheckAppleCollisions(Game& game);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinitializeGame(Game& game);
    void AddPlayerToLeaderboard(Game& game);
}
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
#include <stack>

namespace ApplesGame
{
    enum class GameStatus 
    {
        MainMenu,
        Playing,
        Pause,
        GameOver,
        Win,
        ExitConfirmation,
        Leaderboard
    };

    struct Game
    {
        Player player;
        Stone stones[NUM_STONES];

        std::vector<Apple> applesDynamic;
        std::vector <bool> applesEaten;

        int applesGoal = 0;

        uint32_t modeFlags = 0;

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
        std::stack<GameStatus> stateStack;

        void PushState(GameStatus state)
        {
            stateStack.push(state);
        }
        void PopState()

        {
            if (!stateStack.empty())
                stateStack.pop();
        }

        GameStatus GetCurrentState() const
        {
            if (stateStack.empty())
                return GameStatus::MainMenu;
            return stateStack.top();
        }

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
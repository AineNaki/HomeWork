#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <stack>
#include "Constants.h"
#include "Snake.h"
#include "Apple.h"
#include "UI.h"
#include "Wall.h"
#include "Sound.h"

namespace SnakeGame
{
    enum class GameStatus
    {
        Playing,
        GameOver,
        MainMenu,  
        DifficultyMenu,
        SettingsMenu,
        Pause,           
        ExitConfirmation,
        Leaderboard,
        EnterName
    };

    struct Game
    {
        sf::RenderWindow* window = nullptr;

        Snake snake;
        Apple apples[5];
        UI ui;
        
        //LeaderBoard
        std::map<std::string, int> leaderboard;
        bool waitingForName = false;
        std::string playerName = "Player";
        
        bool gameOverRestartSelected = true;

        //Texture
        sf::Texture menuBgTexture;
        sf::Sprite menuBg;
        sf::Texture backgroundTexture;
        sf::Sprite background;
        sf::Texture snakeHeadRightTex, snakeHeadUpTex, snakeHeadLeftTex, snakeHeadDownTex;
        sf::Texture snakeBodyHorizontalTex, snakeBodyVerticalTex;
        sf::Texture snakeBodyTopLeftTex, snakeBodyTopRightTex, snakeBodyBottomLeftTex, snakeBodyBottomRightTex;
        sf::Texture snakeTailRightTex, snakeTailUpTex, snakeTailLeftTex, snakeTailDownTex;
        sf::Texture appleTexture;
        sf::Texture goldenAppleTexture;
        sf::Texture poisonAppleTexture;

        bool isPoisoned = false;
        float poisonTimer = 0.f;
        float normalSpeed = 0.f;
        int numEatenApples = 0;

        float startDelay = 1.f;
        sf::Clock gameClock;
        float lastTime = 0.f;

        Wall walls[MAX_WALLS];
        int numWalls = 0;
        sf::Texture wallTexture;
        float wallMoveTimer = 0.f;
       
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
                return GameStatus::Playing;
            return stateStack.top();
        }

        uint32_t difficultyFlags = 0;   
        int difficultyLevel = 0;       

        Sound sound;
    };

    void InitGame(Game& game, sf::RenderWindow& window);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game);
    void DeinitializeGame(Game& game);
    void RestartGame(Game& game);
    void ApplyDifficulty(Game& game);
    void HandleGameOver(Game& game);
}
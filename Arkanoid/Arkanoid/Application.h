#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "ArkanoidGame.h"
#include "Menu.h"
#include "UI.h"
#include "Sound.h"

namespace ArkanoidGame
{
    enum class GameState
    {
        MainMenu,
        Playing,
        Pause,
        Settings,
        Leaderboard,
        GameOver,
        EnterName
    };

    class Application
    {
    public:
        Application();
        ~Application();
        void Run();

    private:
        void HandleWindowEvents();
        void HandleMainMenu();
        void HandleSettings();
        void HandleLeaderboard();
        void HandlePause();
        void HandleGameOver();
        void HandleEnterName();

        sf::RenderWindow window;
        sf::Clock gameClock;

        ArkanoidGame game;
        UI ui;
        Menu menu;
        Sound sound;

        sf::Texture menuBgTexture;
        sf::Sprite menuBg;

        std::stack<GameState> stateStack;
        int menuSelection = 0;
        bool gameOverRestartSelected = true;
        bool waitingForName = false;
        int finalScore = 0;
        std::map<std::string, int> leaderboard;
    };
}
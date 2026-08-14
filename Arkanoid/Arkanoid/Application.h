#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include <map>
#include <string>
#include "UI.h"
#include "Menu.h"
#include "Sound.h"
#include "GameContext.h"

namespace ArkanoidGame
{
    class GameStateData;

    class Application
    {
    public:
        Application();
        ~Application();
        void Run();
        void ResetToPlaying();
        void ResetToMainMenu();

        friend class MainMenuState;
        friend class PlayingState;
        friend class PauseState;
        friend class SettingsState;
        friend class LeaderboardState;
        friend class GameOverState;
        friend class WinState;

    private:
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::Clock gameClock;

        UI ui;
        Menu menu;
        Sound sound;
        sf::Texture menuBgTexture;
        sf::Sprite menuBg;
        std::map<std::string, int> leaderboard;
        std::stack<std::unique_ptr<GameStateData>> stateStack;
        GameContext ctx;
    };
}
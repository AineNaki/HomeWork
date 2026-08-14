#include <cstdlib>
#include <ctime>
#include "Application.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "LeaderboardState.h"
#include "GameOverState.h"
#include "Constants.h"

namespace ArkanoidGame
{
    Application::Application()
        : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid"),
        ctx{ window, ui, menu, sound, menuBg, leaderboard, stateStack }
    {
        unsigned int seed = static_cast<unsigned int>(time(nullptr));
        srand(seed);
        window.setFramerateLimit(60);

        InitUI(ui);
        menu.Init(ui);
        sound.LoadSounds(RESOURCES_PATH);
        sound.PlayMusic();

        {
            sf::Image img;
            img.create(SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color(20, 20, 40));
            menuBgTexture.loadFromImage(img);
            menuBg.setTexture(menuBgTexture);
        }

        leaderboard["Player1"] = 100;
        leaderboard["Player2"] = 50;
        leaderboard["Player3"] = 30;

        stateStack.push(std::make_unique<MainMenuState>());

    }

    Application::~Application()
    {
        sound.StopMusic();
    }

    void Application::Run()
    {
        while (window.isOpen())
        {
            HandleWindowEvents();
            if (!window.isOpen()) break;

            float deltaTime = gameClock.restart().asSeconds();

            if (!stateStack.empty())
            {
                stateStack.top()->HandleInput(ctx, *this);
                stateStack.top()->Update(ctx, deltaTime);
                window.clear();
                stateStack.top()->Draw(ctx, window);
                window.display();
            }
        }
    }
    void Application::ResetToPlaying()
    {
        while (!stateStack.empty())
            stateStack.pop();
        stateStack.push(std::make_unique<PlayingState>());
    }

    void Application::ResetToMainMenu()
    {
        while (!stateStack.empty())
            stateStack.pop();
        stateStack.push(std::make_unique<MainMenuState>());
    }

    void Application::HandleWindowEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
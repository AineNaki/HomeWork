#include "Application.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>

namespace ArkanoidGame
{
    Application::Application()
        : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid")
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

        stateStack.push(GameState::MainMenu);
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
            GameState currentState = stateStack.top();

            if (currentState == GameState::MainMenu)
            {
                HandleMainMenu();
                continue;
            }
            if (currentState == GameState::Settings)
            {
                HandleSettings();
                continue;
            }
            if (currentState == GameState::Leaderboard)
            {
                HandleLeaderboard();
                continue;
            }
            if (currentState == GameState::GameOver)
            {
                HandleGameOver();
            }
            if (currentState == GameState::EnterName)
            {
                HandleEnterName();
                continue;
            }
            if (currentState == GameState::Pause)
            {
                HandlePause();
            }

            if (currentState == GameState::Playing)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    stateStack.push(GameState::Pause);
                    sf::sleep(sf::milliseconds(200));
                    continue;
                }
                window.clear();
                game.Draw();
                window.display();
                game.Update(deltaTime);
            }
        }
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

    void Application::HandleMainMenu()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            menu.MoveUp();
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            menu.MoveDown();
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int sel = menu.GetSelectedItem();
            if (sel == 0)
            {
                game.Init(window);
                stateStack.push(GameState::Playing);
            }
            else if (sel == 1)
                stateStack.push(GameState::Leaderboard);
            else if (sel == 2)
                stateStack.push(GameState::Settings);
            else if (sel == 3)
                window.close();
            sf::sleep(sf::milliseconds(200));
        }
        menu.Draw(window, menuBg);
    }

    void Application::HandleSettings()
    {
        static int settingsSelection = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            settingsSelection = (settingsSelection - 1 + 3) % 3;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            settingsSelection = (settingsSelection + 1) % 3;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (settingsSelection == 0) { sound.IncreaseSoundVolume(); sound.PlayEat(); }
            else if (settingsSelection == 1) sound.IncreaseMusicVolume();
            sf::sleep(sf::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (settingsSelection == 0) { sound.DecreaseSoundVolume(); sound.PlayEat(); }
            else if (settingsSelection == 1) sound.DecreaseMusicVolume();
            sf::sleep(sf::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && settingsSelection == 2)
        {
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        DrawSettingsMenu(ui, window, settingsSelection,
            sound.GetSoundVolume(), sound.GetMusicVolume(), menuBg);
    }

    void Application::HandleLeaderboard()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        DrawLeaderboard(ui, window, leaderboard, menuBg);
    }

    void Application::HandlePause()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            stateStack.pop();
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        window.clear();
        game.Draw();                         
        DrawUI(ui, window, true);
        window.display();
    }

    void Application::HandleGameOver()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            stateStack.pop();
            game.Init(window);
            stateStack.push(GameState::Playing);
            sf::sleep(sf::milliseconds(200));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        DrawGameOverScreen(window, ui, menuBg, 0, leaderboard, true);
    }

    void Application::HandleEnterName()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        DrawEnterName(ui, window, "Player", true, menuBg);
    }
}
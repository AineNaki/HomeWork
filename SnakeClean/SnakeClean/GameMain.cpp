#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Constants.h"
#include "Game.h"
#include "Sound.h"

using namespace SnakeGame;

// ===== ÎÁÐÀÁÎÒ×ÈÊÈ ÑÎÑÒÎßÍÈÉ =====

void HandleMainMenu(Game& game, sf::RenderWindow& window, int& menuSelection)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        menuSelection = (menuSelection - 1 + 4) % 4;
        sf::sleep(sf::milliseconds(150));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        menuSelection = (menuSelection + 1) % 4;
        sf::sleep(sf::milliseconds(150));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (menuSelection == 0)
            game.PushState(GameStatus::DifficultyMenu);
        else if (menuSelection == 1)
            game.PushState(GameStatus::Leaderboard);
        else if (menuSelection == 2)
            game.PushState(GameStatus::SettingsMenu);
        else if (menuSelection == 3)
            window.close();
        sf::sleep(sf::milliseconds(200));
    }
    DrawMainMenu(game.ui, window, menuSelection, game.menuBg);
}

void HandleDifficultyMenu(Game& game, sf::RenderWindow& window)
{
    static int diffSelection = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        diffSelection = (diffSelection - 1 + 6) % 6;
        sf::sleep(sf::milliseconds(150));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        diffSelection = (diffSelection + 1) % 6;
        sf::sleep(sf::milliseconds(150));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (diffSelection >= 0 && diffSelection <= 4)
        {
            game.difficultyLevel = diffSelection;
            ApplyDifficulty(game);
            game.PopState();
            game.PushState(GameStatus::Playing);
            RestartGame(game);
        }
        else if (diffSelection == 5)
            game.PopState();
        sf::sleep(sf::milliseconds(200));
    }
    DrawDifficultyMenu(game.ui, window, diffSelection, game.menuBg);
}

void HandleSettingsMenu(Game& game, sf::RenderWindow& window)
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
        if (settingsSelection == 0)
        {
            game.sound.IncreaseSoundVolume();
            game.sound.PlayEat();
        }
        else if (settingsSelection == 1)
            game.sound.IncreaseMusicVolume();
        sf::sleep(sf::milliseconds(100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (settingsSelection == 0)
        {
            game.sound.DecreaseSoundVolume();
            game.sound.PlayEat();
        }
        else if (settingsSelection == 1)
            game.sound.DecreaseMusicVolume();
        sf::sleep(sf::milliseconds(100));
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && settingsSelection == 2)
    {
        game.PopState();
        sf::sleep(sf::milliseconds(200));
    }
    DrawSettingsMenu(game.ui, window, settingsSelection,
        game.sound.GetSoundVolume(), game.sound.GetMusicVolume(), game.menuBg);
}

void HandleLeaderboard(Game& game, sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
    {
        game.PopState();
        sf::sleep(sf::milliseconds(200));
    }
    DrawLeaderboard(game.ui, window, game.leaderboard, game.menuBg);
}

void HandleGameOverState(Game& game)
{
    if (game.waitingForName)
    {
        game.waitingForName = false;
        game.PushState(GameStatus::EnterName);
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.gameOverRestartSelected = !game.gameOverRestartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.gameOverRestartSelected = !game.gameOverRestartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (game.gameOverRestartSelected)
            {
                game.PopState();
                RestartGame(game);
            }
            else
            {
                game.PopState();
                game.PushState(GameStatus::MainMenu);
            }
            sf::sleep(sf::milliseconds(200));
        }
    }
}

void HandleEnterName(Game& game, sf::RenderWindow& window)
{
    static bool saveSelected = false;
    static std::string nameInput = "XYZ";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        saveSelected = !saveSelected;
        sf::sleep(sf::milliseconds(150));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (saveSelected)
            game.leaderboard[nameInput] = game.numEatenApples;
        game.waitingForName = false;
        nameInput = "XYZ";
        saveSelected = false;
        game.PopState();
        sf::sleep(sf::milliseconds(200));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && nameInput.size() > 0)
    {
        nameInput.pop_back();
        sf::sleep(sf::milliseconds(100));
    }
    for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; ++key)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
        {
            if (nameInput.size() < 12)
            {
                char c = static_cast<char>('A' + (key - sf::Keyboard::A));
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
                    !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    c = c - 'A' + 'a';
                nameInput += c;
            }
            sf::sleep(sf::milliseconds(100));
        }
    }
    DrawEnterName(game.ui, window, nameInput, saveSelected, game.menuBg);
}

void HandlePause(Game& game)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        game.PopState();
        game.PopState();
        game.PushState(GameStatus::MainMenu);
        sf::sleep(sf::milliseconds(200));
    }
}

// ===== MAIN =====

int main()
{
    srand(static_cast<int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game!");
    window.setFramerateLimit(60);

    Game game;
    InitGame(game, window);

    int menuSelection = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        GameStatus currentState = game.GetCurrentState();

        if (currentState == GameStatus::MainMenu)
        {
            HandleMainMenu(game, window, menuSelection);
            continue;
        }
        if (currentState == GameStatus::DifficultyMenu)
        {
            HandleDifficultyMenu(game, window);
            continue;
        }
        if (currentState == GameStatus::SettingsMenu)
        {
            HandleSettingsMenu(game, window);
            continue;
        }
        if (currentState == GameStatus::Leaderboard)
        {
            HandleLeaderboard(game, window);
            continue;
        }
        if (currentState == GameStatus::GameOver)
        {
            HandleGameOverState(game);
        }
        if (currentState == GameStatus::EnterName)
        {
            HandleEnterName(game, window);
            continue;
        }
        if (currentState == GameStatus::Pause)
        {
            HandlePause(game);
        }

        float currentTime = game.gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - game.lastTime;
        game.lastTime = currentTime;

        UpdateGame(game, deltaTime);
        DrawGame(game);
    }

    DeinitializeGame(game);
    return 0;
}
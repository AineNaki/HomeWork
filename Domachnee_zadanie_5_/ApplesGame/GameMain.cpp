#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "Math.h"
#include "Player.h"
#include "Constants.h"
#include "Game.h"


int main()
{
    using namespace ApplesGame;
    srand((int)time(nullptr));
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

    Game game;
    InitGame(game);

    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(15));
        float currentTime = game.gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - game.lastTime;
        game.lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                GameStatus cur = game.GetCurrentState();
                if (cur == GameStatus::Playing || cur == GameStatus::GameOver || cur == GameStatus::Win)
                {
                    game.PushState(GameStatus::ExitConfirmation);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                if (game.GetCurrentState() == GameStatus::Playing)
                {
                    game.PushState(GameStatus::Pause);
                }
            }
        }

        GameStatus currentState = game.GetCurrentState();

       if (currentState == GameStatus::MainMenu)
       {
           static int selected = 0; // 0..4
           window.clear(sf::Color::Black);
           DrawMainMenu(window, game.font, selected);
           window.display();

           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
               selected = (selected - 1 + 6) % 6;
               sf::sleep(sf::milliseconds(150));
           }
           else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
               selected = (selected + 1) % 6;
               sf::sleep(sf::milliseconds(150));
           }
           else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
               if (selected == 0) {
                   game.modeFlags = static_cast<uint32_t>(GameModeFlags::SpeedUp);
                   ApplyGameMode(game);
                   game.PopState();
                   game.PushState(GameStatus::Playing);
               }
               else if (selected == 1) {
                   game.modeFlags = static_cast<uint32_t>(GameModeFlags::None);
                   ApplyGameMode(game);
                   game.PopState();
                   game.PushState(GameStatus::Playing);
               }
               else if (selected == 2) {
                   game.modeFlags = static_cast<uint32_t>(GameModeFlags::SpeedUp) | static_cast<uint32_t>(GameModeFlags::FiftyApples);
                   ApplyGameMode(game);
                   game.PopState();
                   game.PushState(GameStatus::Playing);
               }
               else if (selected == 3) {
                   game.modeFlags = static_cast<uint32_t>(GameModeFlags::FiniteGoal);
                   ApplyGameMode(game);
                   game.PopState();
                   game.PushState(GameStatus::Playing);
               }
               else if (selected == 4) {
                   game.PushState(GameStatus::Leaderboard);
               }
               else if (selected == 5) {
                   window.close();
               }
               sf::sleep(sf::milliseconds(200));
           }
           continue;
           }


        else if (currentState == GameStatus::Playing)
        {
            UpdateGame(game, deltaTime);
            window.clear();
            DrawGame(game, window);
            window.display();
        }

        else if (currentState == GameStatus::GameOver)
        {
            window.clear();
            DrawLeaderboard(window, game.font, game.leaderboard);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                while (!game.stateStack.empty())
                    game.stateStack.pop();
                game.stateStack.push(GameStatus::MainMenu);
                sf::sleep(sf::milliseconds(200));
            }
            continue;
        }

        else if (currentState == GameStatus::Win)
        {
            window.clear();
            DrawLeaderboard(window, game.font, game.leaderboard);
            window.draw(game.ui.winText);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                while (!game.stateStack.empty())
                    game.stateStack.pop();
                game.stateStack.push(GameStatus::MainMenu);
                sf::sleep(sf::milliseconds(200));
            }
            continue;
        }


        else if (currentState == GameStatus::ExitConfirmation)
        {
            window.clear();
            DrawExitConfirmation(window, game.font);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                game.PopState();
            }
            continue;
        }

        else if (currentState == GameStatus::Leaderboard)

        {
            window.clear();
            DrawLeaderboardState(window, game.font, game.leaderboard);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
            {
                game.PopState();
                sf::sleep(sf::milliseconds(200));
            }
            continue;
        }

        else if (currentState == GameStatus::Pause)
        {
            static int selected = 0;
            window.clear();
            DrawPauseMenu(window, game.font, selected);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                selected = (selected - 1 + 2) % 2;
                sf::sleep(sf::milliseconds(150));

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                selected = (selected + 1) % 2;
                sf::sleep(sf::milliseconds(150));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (selected == 0)
                {
                    game.PopState();
                }
                else
                {
                  
                    while (!game.stateStack.empty())
                        game.stateStack.pop();
                    game.stateStack.push(GameStatus::MainMenu);
                }
                sf::sleep(sf::milliseconds(200));
            }
            continue;
            }
        }
    

    DeinitializeGame(game);
    return 0;
}

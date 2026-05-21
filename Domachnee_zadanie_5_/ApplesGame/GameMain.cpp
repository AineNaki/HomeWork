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

    game.isInMainMenu = true;
   

    while (window.isOpen())
    {
        //Reduce framerate to not spam CPU and GPU
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
                window.close();
        }
        if (game.isInMainMenu) {
            window.clear(sf::Color::Black);
            DrawMainMenu(window, game.font);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                game.modeFlags = static_cast<uint32_t>(GameModeFlags::SpeedUp);
                ApplyGameMode(game);
                game.isInMainMenu = false;
                std::cout << "Mode 1 selected\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                game.modeFlags = static_cast<uint32_t>(GameModeFlags::None);
                ApplyGameMode(game);
                game.isInMainMenu = false;
                std::cout << "Mode 2 selected\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                game.modeFlags = static_cast<uint32_t>(GameModeFlags::SpeedUp) |
                    static_cast<uint32_t>(GameModeFlags::FiftyApples);
                ApplyGameMode(game);
                game.isInMainMenu = false;
                std::cout << "Mode 3 selected\n";
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                game.modeFlags = static_cast<uint32_t>(GameModeFlags::FiniteGoal);
                ApplyGameMode(game);
                game.isInMainMenu = false;
                std::cout << "Mode 4 selected: Finite goal (random), no acceleration\n";
            }

            continue; 
        }

        UpdateGame(game, deltaTime);

        window.clear(); 
        DrawGame(game, window);
        window.display();
    }

    DeinitializeGame(game);
    return 0;
}


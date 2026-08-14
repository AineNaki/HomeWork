#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include <map>
#include <string>
#include "UI.h"
#include "Menu.h"
#include "Sound.h"

namespace ArkanoidGame
{
    class GameStateData;

    struct GameContext
    {
        sf::RenderWindow& window;
        UI& ui;
        Menu& menu;
        Sound& sound;
        sf::Sprite& menuBg;
        std::map<std::string, int>& leaderboard;
        std::stack<std::unique_ptr<GameStateData>>& stateStack;
    };
}
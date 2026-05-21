#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h" 
#include <vector>
#include <string>

namespace ApplesGame
{
    struct UI
    {
        sf::Text scoreText;
        sf::Text controlsText;
        sf::Text gameOverText;
        sf::Text winText;
        sf::Text goalText;

    };

    struct Record {
        std::string name;
        int score;
    };

    void DrawMainMenu(sf::RenderWindow& window, const sf::Font& font);

    void InitUI(UI& ui, const sf::Font& font);

    void UpdateUIScore(UI& ui, int numEatenApples);

    void DrawUI(UI& ui, sf::RenderWindow& window);

    void DrawLeaderboard(sf::RenderWindow& window, const sf::Font& font, const std::map<std::string, int>& leaderboard);

}

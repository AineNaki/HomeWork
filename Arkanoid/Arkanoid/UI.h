#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ArkanoidGame
{
    struct UI
    {
        sf::Font font;
        sf::Text scoreText;
        sf::Text pauseText;
        sf::Text pauseMenuText;
    };

    void InitUI(UI& ui);
    void UpdateUIScore(UI& ui, int score);
    void DrawUI(UI& ui, sf::RenderWindow& window, bool isPaused);
    void DrawDifficultyMenu(UI& ui, sf::RenderWindow& window, int selectedItem, const sf::Sprite& menuBg);
    void DrawSettingsMenu(UI& ui, sf::RenderWindow& window, int selectedItem, float soundVolume, float musicVolume, const sf::Sprite& menuBg);
    void DrawLeaderboard(UI& ui, sf::RenderWindow& window, const std::map<std::string, int>& leaderboard, const sf::Sprite& menuBg);
    void DrawEnterName(UI& ui, sf::RenderWindow& window, const std::string& playerName, bool saveSelected, const sf::Sprite& menuBg);
    void DrawGameOverScreen(sf::RenderWindow& window, const UI& ui, const sf::Sprite& menuBg, int finalScore, const std::map<std::string, int>& leaderboard, bool restartSelected);
    void DrawGoText(sf::RenderWindow& window, const sf::Font& font);
}
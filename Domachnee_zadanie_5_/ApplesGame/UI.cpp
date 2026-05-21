#include "UI.h"
#include <string>
#include <map>



namespace ApplesGame
{

    void DrawMainMenu(sf::RenderWindow& window, const sf::Font& font)
    {
        sf::Text title;
        title.setFont(font);
        title.setString("Select Game Mode:");
        title.setCharacterSize(36);
        title.setFillColor(sf::Color(255,80,155));
        title.setPosition(SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, 100);
        window.draw(title);

        sf::Text mode1;
        mode1.setFont(font);
        mode1.setString("1 - 20 apples, with acceleration");
        mode1.setCharacterSize(28);
        mode1.setFillColor(sf::Color(213, 100, 124));
        mode1.setPosition(SCREEN_WIDTH / 2 - mode1.getLocalBounds().width / 2, 210);
        window.draw(mode1);

        sf::Text mode2;
        mode2.setFont(font);
        mode2.setString("2 - 20 apples, no acceleration");
        mode2.setCharacterSize(28);
        mode2.setFillColor(sf::Color(219, 119, 141));
        mode2.setPosition(SCREEN_WIDTH / 2 - mode2.getLocalBounds().width / 2, 270);
        window.draw(mode2);

        sf::Text mode3;
        mode3.setFont(font);
        mode3.setString("3 - 50 apples, with acceleration");
        mode3.setCharacterSize(28);
        mode3.setFillColor(sf::Color(233,161,176));
        mode3.setPosition(SCREEN_WIDTH / 2 - mode3.getLocalBounds().width / 2, 330);
        window.draw(mode3);

        sf::Text mode4;
        mode4.setFont(font);
        mode4.setString("4 - finite goal, no acceleration");
        mode4.setCharacterSize(28);
        mode4.setFillColor(sf::Color(245, 200, 200));
        mode4.setPosition(SCREEN_WIDTH / 2 - mode4.getLocalBounds().width / 2, 400);
        window.draw(mode4);
    }

    void InitUI(UI& ui, const sf::Font& font)
    {
        
        ui.scoreText.setFont(font);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(sf::Color::White);
        ui.scoreText.setPosition(10.f, 10.f);
        ui.scoreText.setString("Apples eaten: 0");
        
        ui.controlsText.setFont(font);
        ui.controlsText.setString("Controls: Arrow keys | Space - restart | Esc - exit");
        ui.controlsText.setCharacterSize(16);
        ui.controlsText.setFillColor(sf::Color::White);
     
        sf::FloatRect bounds = ui.controlsText.getLocalBounds();
        ui.controlsText.setOrigin(bounds.width / 2.f, 0);
        ui.controlsText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 25);
        
        ui.gameOverText.setFont(font);
        ui.gameOverText.setString("GAME OVER");
        ui.gameOverText.setCharacterSize(48);
        ui.gameOverText.setFillColor(sf::Color::White);

        sf::FloatRect gameOverBounds = ui.gameOverText.getLocalBounds();
        ui.gameOverText.setOrigin(gameOverBounds.width / 2.f, gameOverBounds.height / 2.f);
        ui.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        ui.winText.setFont(font);
        ui.winText.setString("YOU WIN!");
        ui.winText.setCharacterSize(48);
        ui.winText.setFillColor(sf::Color::White);
        ui.winText.setOrigin(ui.winText.getLocalBounds().width / 2, ui.winText.getLocalBounds().height / 2);
        ui.winText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        ui.goalText.setFont(font);
        ui.goalText.setCharacterSize(20);
        ui.goalText.setFillColor(sf::Color::White);
        ui.goalText.setPosition(10.f, 40.f);
        ui.goalText.setString("");
    }

    void UpdateUIScore(UI& ui, int numEatenApples)
    {
        ui.scoreText.setString("Apples eaten: " + std::to_string(numEatenApples));
    }

    void DrawLeaderboard(sf::RenderWindow& window, const sf::Font& font, const std::map<std::string, int>& leaderboard)
    {
        if (leaderboard.empty()) return;

        std::vector<std::pair<std::string, int>> vec(leaderboard.begin(), leaderboard.end());

        for (size_t i = 0; i < vec.size() - 1; ++i) 
        {
            for (size_t j = 0; j < vec.size() - i - 1; ++j)
            {
                if (vec[j].second < vec[j + 1].second)
                {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }

        sf::Text title;
        title.setFont(font);
        title.setString("===== LEADERBOARD =====");
        title.setCharacterSize(28);
        title.setFillColor(sf::Color::White);
        title.setPosition(SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - 150);
        window.draw(title);

        float yOffset = SCREEN_HEIGHT / 2 - 100;
        for (size_t i = 0; i < vec.size(); ++i) 
        {
            sf::Text entry;
            entry.setFont(font);
            std::string line = std::to_string(i + 1) + ". " + vec[i].first + " ......... " + std::to_string(vec[i].second);
            entry.setString(line);
            entry.setCharacterSize(22);
            entry.setFillColor(sf::Color::White);
            entry.setPosition(SCREEN_WIDTH / 2 - entry.getLocalBounds().width / 2, yOffset);
            window.draw(entry);
            yOffset += 30;
        }
    }

    void DrawUI(UI& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
        window.draw(ui.controlsText);
    }
}
#include "UI.h"
#include <string>
#include <map>



namespace ApplesGame
{

    void DrawMainMenu(sf::RenderWindow& window, const sf::Font& font, int selectedItem)
    {
        std::vector<std::string> items = {
            "1. 20 apples, with acceleration",
            "2. 20 apples, no acceleration",
            "3. 50 apples, with acceleration",
            "4. Finite goal (20-50 apples), no acceleration",
            "5. Leaderboard",
            "6. Exit"
        };

        sf::Text title;
        title.setFont(font);
        title.setString("Select Game Mode:");
        title.setCharacterSize(36);
        title.setFillColor(sf::Color(0, 255, 255));
        title.setPosition(SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, 60);
        window.draw(title);

        for (size_t i = 0; i < items.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(items[i]);
            item.setCharacterSize(28);
            item.setFillColor(sf::Color(213, 100, 124));
            if (i == selectedItem) {
                item.setOutlineThickness(2);
                item.setOutlineColor(sf::Color(0, 255, 255));
            }
            item.setPosition(SCREEN_WIDTH / 2 - item.getLocalBounds().width / 2, 140 + i * 60);
            window.draw(item);
        }
    }
   

    void DrawExitConfirmation(sf::RenderWindow& window, const sf::Font& font)
    {
        sf::Text confirmText;
        confirmText.setFont(font);
        confirmText.setString("Do you want to exit? (Y/N)");
        confirmText.setCharacterSize(30);
        confirmText.setFillColor(sf::Color::White);
        confirmText.setPosition(SCREEN_WIDTH / 2 - confirmText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2);
        window.draw(confirmText);
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
        ui.winText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 200);

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

    void DrawLeaderboardState(sf::RenderWindow& window, const sf::Font& font, const std::map<std::string, int>& leaderboard)
    {
   
        DrawLeaderboard(window, font, leaderboard);

        sf::Text backText;
        backText.setFont(font);
        backText.setString("Press Backspace to return to menu");
        backText.setCharacterSize(20);
        backText.setFillColor(sf::Color::White);
        backText.setPosition(SCREEN_WIDTH / 2 - backText.getLocalBounds().width / 2, SCREEN_HEIGHT - 50);
        window.draw(backText);
    }

    void DrawPauseMenu(sf::RenderWindow& window, const sf::Font& font, int selectedItem)
    {
        sf::Text title;
        title.setFont(font);
        title.setString("PAUSE");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - 150);
        window.draw(title);

        std::vector<std::string> items = { "Continue", "Exit to Menu" };
        for (size_t i = 0; i < items.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(items[i]);
            item.setCharacterSize(32);
            item.setFillColor(sf::Color::White);
            if (i == selectedItem) {
                item.setOutlineThickness(2);
                item.setOutlineColor(sf::Color::Yellow);
            }
            item.setPosition(SCREEN_WIDTH / 2 - item.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 + i * 60);
            window.draw(item);
        }
    }

    void DrawUI(UI& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
        window.draw(ui.controlsText);
    }




}
#include "UI.h"
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

namespace ArkanoidGame
{
    void InitUI(UI& ui)
    {
        assert(ui.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        // PAUSE
        ui.pauseText.setFont(ui.font);
        ui.pauseText.setString("PAUSE");
        ui.pauseText.setCharacterSize(48);
        ui.pauseText.setFillColor(sf::Color::Yellow);
        sf::FloatRect pBounds = ui.pauseText.getLocalBounds();
        ui.pauseText.setOrigin(pBounds.width / 2.f, pBounds.height / 2.f);
        ui.pauseText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 60);

        ui.pauseMenuText.setFont(ui.font);
        ui.pauseMenuText.setString("Press P to resume\nPress Esc to quit");
        ui.pauseMenuText.setCharacterSize(24);
        ui.pauseMenuText.setFillColor(sf::Color(255, 182, 193));
        sf::FloatRect pmBounds = ui.pauseMenuText.getLocalBounds();
        ui.pauseMenuText.setOrigin(pmBounds.width / 2.f, pmBounds.height / 2.f);
        ui.pauseMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 20);

        // Ñ÷¸ò
        ui.scoreText.setFont(ui.font);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(sf::Color(255, 182, 193));
        ui.scoreText.setPosition(SCREEN_WIDTH - 10.f, 10.f);
        ui.scoreText.setOrigin(ui.scoreText.getLocalBounds().width, 0.f);
        ui.scoreText.setString("Score: 0");
    }

    void UpdateUIScore(UI& ui, int score)
    {
        ui.scoreText.setString("Score: " + std::to_string(score));
        ui.scoreText.setOrigin(ui.scoreText.getLocalBounds().width, 0.f);
    }

    void DrawUI(UI& ui, sf::RenderWindow& window, bool isPaused)
    {
        window.draw(ui.scoreText);

        if (isPaused)
        {
            window.draw(ui.pauseText);
            window.draw(ui.pauseMenuText);
        }
    }

    void DrawDifficultyMenu(UI& ui, sf::RenderWindow& window, int selectedItem, const sf::Sprite& menuBg)
    {
       
        window.draw(menuBg);

        sf::Text title;
        title.setFont(ui.font);
        title.setString("SELECT DIFFICULTY");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Yellow);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, MENU_TITLE_Y);
        window.draw(title);

        std::vector<std::string> items = { "1. Easy", "2. Normal", "3. Hard", "4. Expert", "5. Insane", "6. Back" };
        for (size_t i = 0; i < items.size(); ++i)
        {
            sf::Text item;
            item.setFont(ui.font);
            item.setString(items[i]);
            item.setCharacterSize(28);
            item.setFillColor(i == selectedItem ? sf::Color::Green : sf::Color(255, 182, 193));
            sf::FloatRect b = item.getLocalBounds();
            item.setOrigin(b.width / 2.f, b.height / 2.f);
            item.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y + i * MENU_ITEM_SPACING);
            window.draw(item);
        }
       
    }

    void DrawSettingsMenu(UI& ui, sf::RenderWindow& window, int selectedItem, float soundVolume, float musicVolume, const sf::Sprite& menuBg)
    {
       
        window.draw(menuBg);

        sf::Text title;
        title.setFont(ui.font);
        title.setString("SETTINGS");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Yellow);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, MENU_TITLE_Y);
        window.draw(title);

        sf::Text soundText;
        soundText.setFont(ui.font);
        soundText.setString("Sound: " + std::to_string((int)soundVolume) + "%");
        soundText.setCharacterSize(28);
        soundText.setFillColor(selectedItem == 0 ? sf::Color::Green : sf::Color(255, 182, 193));
        sf::FloatRect sb = soundText.getLocalBounds();
        soundText.setOrigin(sb.width / 2.f, sb.height / 2.f);
        soundText.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y);
        window.draw(soundText);

        sf::Text musicText;
        musicText.setFont(ui.font);
        musicText.setString("Music: " + std::to_string((int)musicVolume) + "%");
        musicText.setCharacterSize(28);
        musicText.setFillColor(selectedItem == 1 ? sf::Color::Green : sf::Color(255, 182, 193));
        sf::FloatRect mb = musicText.getLocalBounds();
        musicText.setOrigin(mb.width / 2.f, mb.height / 2.f);
        musicText.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y + MENU_ITEM_SPACING);
        window.draw(musicText);

        sf::Text backText;
        backText.setFont(ui.font);
        backText.setString("Back");
        backText.setCharacterSize(28);
        backText.setFillColor(selectedItem == 2 ? sf::Color::Green : sf::Color(255, 182, 193));
        sf::FloatRect bb = backText.getLocalBounds();
        backText.setOrigin(bb.width / 2.f, bb.height / 2.f);
        backText.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y + 2 * MENU_ITEM_SPACING);
        window.draw(backText);

       
    }

    void DrawLeaderboard(UI& ui, sf::RenderWindow& window, const std::map<std::string, int>& leaderboard, const sf::Sprite& menuBg)
    {
       
        window.draw(menuBg);

        sf::Text title;
        title.setFont(ui.font);
        title.setString("LEADERBOARD");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Yellow);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, MENU_TITLE_Y);
        window.draw(title);

        std::vector<std::pair<std::string, int>> vec(leaderboard.begin(), leaderboard.end());
        for (size_t i = 0; i < vec.size() - 1; ++i)
            for (size_t j = 0; j < vec.size() - i - 1; ++j)
                if (vec[j].second < vec[j + 1].second)
                    std::swap(vec[j], vec[j + 1]);

        for (size_t i = 0; i < vec.size() && i < 10; ++i)
        {
            sf::Text entry;
            entry.setFont(ui.font);
            entry.setString(std::to_string(i + 1) + ". " + vec[i].first + " - " + std::to_string(vec[i].second));
            entry.setCharacterSize(24);
            entry.setFillColor(sf::Color(255, 182, 193));
            sf::FloatRect eb = entry.getLocalBounds();
            entry.setOrigin(eb.width / 2.f, eb.height / 2.f);
            entry.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y + i * MENU_ITEM_SPACING);
            window.draw(entry);
        }

        sf::Text backText;
        backText.setFont(ui.font);
        backText.setString("Press Backspace to return");
        backText.setCharacterSize(20);
        backText.setFillColor(sf::Color::White);
        sf::FloatRect bb = backText.getLocalBounds();
        backText.setOrigin(bb.width / 2.f, bb.height / 2.f);
        backText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 30);
        window.draw(backText);

    }

    void DrawEnterName(UI& ui, sf::RenderWindow& window, const std::string& playerName, bool saveSelected, const sf::Sprite& menuBg)
    {
       
        window.draw(menuBg);

        sf::Text title;
        title.setFont(ui.font);
        title.setString("NEW RECORD!");
        title.setCharacterSize(36);
        title.setFillColor(sf::Color::Yellow);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, 150);
        window.draw(title);

        sf::Text nameText;
        nameText.setFont(ui.font);
        nameText.setString("Name: " + playerName + "_");
        nameText.setCharacterSize(28);
        nameText.setFillColor(sf::Color(255, 182, 193));
        sf::FloatRect nb = nameText.getLocalBounds();
        nameText.setOrigin(nb.width / 2.f, nb.height / 2.f);
        nameText.setPosition(SCREEN_WIDTH / 2.f, 220);
        window.draw(nameText);

        sf::Text saveText;
        saveText.setFont(ui.font);
        saveText.setString("Save to leaderboard?");
        saveText.setCharacterSize(24);
        saveText.setFillColor(sf::Color(255, 182, 193));
        sf::FloatRect sb = saveText.getLocalBounds();
        saveText.setOrigin(sb.width / 2.f, sb.height / 2.f);
        saveText.setPosition(SCREEN_WIDTH / 2.f, 280);
        window.draw(saveText);

        sf::Text yesText;
        yesText.setFont(ui.font);
        yesText.setString("> Yes");
        yesText.setCharacterSize(28);
        yesText.setFillColor(saveSelected ? sf::Color::Green : sf::Color(255, 182, 193));
        sf::FloatRect yb = yesText.getLocalBounds();
        yesText.setOrigin(yb.width / 2.f, yb.height / 2.f);
        yesText.setPosition(SCREEN_WIDTH / 2.f, 330);
        window.draw(yesText);

        sf::Text noText;
        noText.setFont(ui.font);
        noText.setString("  No");
        noText.setCharacterSize(28);
        noText.setFillColor(!saveSelected ? sf::Color::Green : sf::Color(255, 182, 193));
        sf::FloatRect nob = noText.getLocalBounds();
        noText.setOrigin(nob.width / 2.f, nob.height / 2.f);
        noText.setPosition(SCREEN_WIDTH / 2.f, 370);
        window.draw(noText);

      
    }

    void DrawGameOverScreen(sf::RenderWindow& window, const UI& ui, const sf::Sprite& menuBg, int finalScore, const std::map<std::string, int>& leaderboard, bool restartSelected)
    {
        window.draw(menuBg);

        sf::Text gameOverTitle;
        gameOverTitle.setFont(ui.font);
        gameOverTitle.setString("GAME OVER");
        gameOverTitle.setCharacterSize(48);
        gameOverTitle.setFillColor(sf::Color::Red);
        sf::FloatRect gob = gameOverTitle.getLocalBounds();
        gameOverTitle.setOrigin(gob.width / 2.f, gob.height / 2.f);
        gameOverTitle.setPosition(SCREEN_WIDTH / 2.f, 80);
        window.draw(gameOverTitle);

        sf::Text finalScoreText;
        finalScoreText.setFont(ui.font);
        finalScoreText.setString("Final Score: " + std::to_string(finalScore));
        finalScoreText.setCharacterSize(28);
        finalScoreText.setFillColor(sf::Color(0, 200, 100));
        finalScoreText.setOutlineThickness(2.f);
        finalScoreText.setOutlineColor(sf::Color::White);
        sf::FloatRect fb = finalScoreText.getLocalBounds();
        finalScoreText.setPosition(SCREEN_WIDTH - 10.f, 10.f);
        finalScoreText.setOrigin(finalScoreText.getLocalBounds().width, 0.f);
        window.draw(finalScoreText);

        sf::Text title;
        title.setFont(ui.font);
        title.setString("LEADERBOARD");
        title.setCharacterSize(24);
        title.setFillColor(sf::Color(255, 165, 0));
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, 150);
        window.draw(title);

        std::vector<std::pair<std::string, int>> vec(leaderboard.begin(), leaderboard.end());
        for (size_t i = 0; i < vec.size() - 1; ++i)
            for (size_t j = 0; j < vec.size() - i - 1; ++j)
                if (vec[j].second < vec[j + 1].second)
                    std::swap(vec[j], vec[j + 1]);

        for (size_t i = 0; i < vec.size() && i < 10; ++i)
        {
            sf::Text entry;
            entry.setFont(ui.font);
            entry.setString(std::to_string(i + 1) + ". " + vec[i].first + " - " + std::to_string(vec[i].second));
            entry.setCharacterSize(18);
            entry.setFillColor(sf::Color(0, 200, 100));
            sf::FloatRect eb = entry.getLocalBounds();
            entry.setOrigin(eb.width / 2.f, eb.height / 2.f);
            entry.setPosition(SCREEN_WIDTH / 2.f, 185 + i * 30);
            window.draw(entry);
        }

        sf::Text restartBtn;
        restartBtn.setFont(ui.font);
        restartBtn.setString("Restart");
        restartBtn.setCharacterSize(28);
        restartBtn.setFillColor(restartSelected ? sf::Color::Green : sf::Color(0, 200, 100));
        sf::FloatRect rb = restartBtn.getLocalBounds();
        restartBtn.setOrigin(rb.width / 2.f, rb.height / 2.f);
        restartBtn.setPosition(SCREEN_WIDTH / 2.f - 70, SCREEN_HEIGHT - 75);
        window.draw(restartBtn);

        sf::Text menuBtn;
        menuBtn.setFont(ui.font);
        menuBtn.setString("Menu");
        menuBtn.setCharacterSize(28);
        menuBtn.setFillColor(!restartSelected ? sf::Color::Green : sf::Color(0, 200, 100));
        sf::FloatRect mb = menuBtn.getLocalBounds();
        menuBtn.setOrigin(mb.width / 2.f, mb.height / 2.f);
        menuBtn.setPosition(SCREEN_WIDTH / 2.f + 70, SCREEN_HEIGHT - 75);
        window.draw(menuBtn);
    }

    void DrawGoText(sf::RenderWindow& window, const sf::Font& font)
    {
        sf::Text goText;
        goText.setFont(font);
        goText.setString("GO!");
        goText.setCharacterSize(64);
        goText.setFillColor(sf::Color::Green);
        sf::FloatRect gb = goText.getLocalBounds();
        goText.setOrigin(gb.width / 2.f, gb.height / 2.f);
        goText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        window.draw(goText);
    }
}
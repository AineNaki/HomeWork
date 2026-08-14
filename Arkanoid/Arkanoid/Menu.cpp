#include "Menu.h"
#include "Constants.h"

namespace ArkanoidGame
{
    void Menu::Init(UI& ui)
    {
        std::vector<std::string> itemStrings = { "Play", "Leaderboard", "Settings", "Exit" };
        for (size_t i = 0; i < itemStrings.size(); ++i)
        {
            sf::Text item;
            item.setFont(ui.font);
            item.setString(itemStrings[i]);
            item.setCharacterSize(32);
            item.setFillColor(sf::Color(255, 182, 193));
            sf::FloatRect bounds = item.getLocalBounds();
            item.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            item.setPosition(SCREEN_WIDTH / 2.f, MENU_ITEMS_START_Y + i * MENU_ITEM_SPACING);
            menuItems.push_back(item);
        }
    }

    void Menu::Draw(sf::RenderWindow& window, const sf::Sprite& menuBg)
    {
        window.draw(menuBg);

        for (size_t i = 0; i < menuItems.size(); ++i)
        {
            menuItems[i].setFillColor(i == selectedItem ? sf::Color(0, 255, 100) : sf::Color(255, 182, 193));
            window.draw(menuItems[i]);
        }
    }

    void Menu::MoveUp()
    {
        selectedItem = (selectedItem - 1 + 4) % 4;
    }

    void Menu::MoveDown()
    {
        selectedItem = (selectedItem + 1) % 4;
    }
}
#include "PlayingState.h"
#include "Application.h"
#include "GameSettings.h"

namespace Roguelike
{
    void PlayingState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            ctx.stateStack.pop();  // back to main menu
            sf::sleep(sf::milliseconds(200));
        }
    }

    void PlayingState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void PlayingState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        window.clear(sf::Color(20, 20, 30));

        sf::Text text;
        text.setFont(ctx.ui.font);
        text.setString("TO BE DONE...\nPress Esc to exit to menu");
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        text.setPosition(
            GameWorld::GetInstance().GetScreenWidth() / 2.f,
            GameWorld::GetInstance().GetScreenHeight() / 2.f);
        window.draw(text);
    }
}
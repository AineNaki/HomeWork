#include "MainMenuState.h"
#include "Application.h"
#include "GameContext.h"
#include "PlayingState.h"
#include "LeaderboardState.h"
#include "SettingsState.h"

namespace ArkanoidGame
{
    void MainMenuState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            ctx.menu.MoveUp();
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            ctx.menu.MoveDown();
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int sel = ctx.menu.GetSelectedItem();
            if (sel == 0)
                ctx.stateStack.push(std::make_unique<PlayingState>());
            else if (sel == 1)
                ctx.stateStack.push(std::make_unique<LeaderboardState>());
            else if (sel == 2)
                ctx.stateStack.push(std::make_unique<SettingsState>());
            else if (sel == 3)
                ctx.window.close();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void MainMenuState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void MainMenuState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        ctx.menu.Draw(window, ctx.menuBg);
    }
}
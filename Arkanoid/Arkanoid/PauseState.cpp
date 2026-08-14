#include "PauseState.h"
#include "Application.h"
#include "GameContext.h"

namespace ArkanoidGame
{
    void PauseState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            ctx.stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            ctx.stateStack.pop();  // Pause
            ctx.stateStack.pop();  // Playing
            sf::sleep(sf::milliseconds(200));
        }
    }

    void PauseState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void PauseState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        DrawUI(ctx.ui, window, true);
    }
}
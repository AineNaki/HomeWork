#include "LeaderboardState.h"
#include "Application.h"
#include "GameContext.h"

namespace ArkanoidGame
{
    void LeaderboardState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            ctx.stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void LeaderboardState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void LeaderboardState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        DrawLeaderboard(ctx.ui, window, ctx.leaderboard, ctx.menuBg);
    }
}
#include "PlayingState.h"
#include "Application.h"
#include "GameContext.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "WinState.h"

namespace ArkanoidGame
{
    void PlayingState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            ctx.stateStack.push(std::make_unique<PauseState>());
            sf::sleep(sf::milliseconds(200));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            ctx.stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void PlayingState::Update(GameContext& ctx, float deltaTime)
    {
        if (!gameStarted)
        {
            game.Init(ctx.window);
            gameStarted = true;
        }
        game.Update(deltaTime);

        if (game.IsWin() && !gameFinished)
        {
            gameFinished = true;
            ctx.stateStack.push(std::make_unique<WinState>());
        }

        if (game.IsBallOutOfBounds() && !gameFinished)
        {
            gameFinished = true;
            ctx.stateStack.push(std::make_unique<GameOverState>(0));
        }
    }

    void PlayingState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        game.Draw();
    }
}
#include "PlayingState.h"
#include "Application.h"
#include "GameContext.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "WinState.h"
#include "Block.h"

namespace ArkanoidGame
{
    void PlayingState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            ctx.stateStack.push(std::make_shared<PauseState>());
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
        this->ctx = &ctx;

        if (!gameStarted)
        {
            game.Init(ctx.window);
            breakableBlocksCount = game.GetBreakableBlocksCount();

            for (auto& block : game.GetBlocks())
            {
                block->AddObserver(shared_from_this());
            }

            gameStarted = true;
        }

        game.Update(deltaTime);

        if (game.IsGameOver() && !gameFinished)
        {
            gameFinished = true;
            ctx.stateStack.push(std::make_shared<GameOverState>(score));
        }
    }

    void PlayingState::Notify(std::shared_ptr<IObservable> observable)
    {
        if (auto block = std::dynamic_pointer_cast<Block>(observable))
        {
            if (block->IsDestroyed())
            {
                score += block->GetScore();
            }
            --breakableBlocksCount;

            if (breakableBlocksCount <= 0 && !gameFinished)
            {
                gameFinished = true;
                if (ctx)
                    ctx->stateStack.push(std::make_shared<WinState>());
            }
        }
    }

    void PlayingState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        game.Draw();
        UpdateUIScore(ctx.ui, score);
        UpdateLives(ctx.ui, game.GetLives());
        window.draw(ctx.ui.scoreText);
        window.draw(ctx.ui.livesText);
        if (game.GetBonusTimer() > 0.f)
        {
            UpdateBonusTimer(ctx.ui, game.GetBonusTimer());
            window.draw(ctx.ui.bonusTimerText);
        }
    }
}
#include "GameOverState.h"
#include "Application.h"
#include "GameContext.h"
#include "PlayingState.h"
#include "MainMenuState.h"

namespace ArkanoidGame
{
    GameOverState::GameOverState(int finalScore)
        : finalScore(finalScore)
    {
    }

    void GameOverState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            restartSelected = !restartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            restartSelected = !restartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (restartSelected)
                app.ResetToPlaying();
            else
                app.ResetToMainMenu();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void GameOverState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void GameOverState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        DrawGameOverScreen(window, ctx.ui, ctx.menuBg, finalScore, ctx.leaderboard, restartSelected);
    }
}
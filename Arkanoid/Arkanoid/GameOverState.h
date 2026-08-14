#pragma once
#include "GameStateData.h"

namespace ArkanoidGame
{
    class GameOverState : public GameStateData
    {
    public:
        explicit GameOverState(int finalScore);
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;

    private:
        int finalScore;
        bool restartSelected = true;
    };
}
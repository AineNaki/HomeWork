#pragma once
#include "GameStateData.h"

namespace ArkanoidGame
{
    class WinState : public GameStateData
    {
    public:
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;

    private:
        bool restartSelected = true;
    };
}
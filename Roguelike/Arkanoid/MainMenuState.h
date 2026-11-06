#pragma once
#include "GameStateData.h"

namespace Roguelike
{
    class MainMenuState : public GameStateData
    {
    public:
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;
    };
}
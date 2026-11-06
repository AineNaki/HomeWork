#pragma once
#include "GameStateData.h"

namespace Roguelike
{
    class SettingsState : public GameStateData
    {
    public:
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;

    private:
        int selection = 0;
    };
}
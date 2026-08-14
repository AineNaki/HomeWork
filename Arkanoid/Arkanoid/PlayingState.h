#pragma once
#include "GameStateData.h"
#include "ArkanoidGame.h"

namespace ArkanoidGame
{
    class PlayingState : public GameStateData
    {
    public:
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;

    private:
        ArkanoidGame game;
        bool gameStarted = false;
        bool gameFinished = false;
    };
}
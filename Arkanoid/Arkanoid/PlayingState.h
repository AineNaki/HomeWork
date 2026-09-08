#pragma once
#include "GameStateData.h"
#include "ArkanoidGame.h"
#include "IObserver.h"

namespace ArkanoidGame
{
    class PlayingState : public GameStateData, public IObserver, public std::enable_shared_from_this<PlayingState>
    {
    public:
        void HandleInput(GameContext& ctx, Application& app) override;
        void Update(GameContext& ctx, float deltaTime) override;
        void Draw(GameContext& ctx, sf::RenderWindow& window) override;
        void Notify(std::shared_ptr<IObservable> observable) override;
        int GetScore() const { return score; }

    private:
        ArkanoidGame game;
        bool gameStarted = false;
        bool gameFinished = false;
        int breakableBlocksCount = 0;
        GameContext* ctx = nullptr;
        int score = 0;
        sf::Text scoreText;
        bool scoreTextInitialized = false;
    };
}
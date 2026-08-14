#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    class Application;
    struct GameContext;

    class GameStateData
    {
    public:
        virtual ~GameStateData() = default;

        virtual void HandleInput(GameContext& ctx, Application& app) = 0;
        virtual void Update(GameContext& ctx, float deltaTime) = 0;
        virtual void Draw(GameContext& ctx, sf::RenderWindow& window) = 0;
    };
}
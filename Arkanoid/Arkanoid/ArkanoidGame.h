#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

namespace ArkanoidGame
{
    class ArkanoidGame
    {
    public:
        void Init(sf::RenderWindow& window);
        void Update(float deltaTime);
        void Draw();

    private:
        sf::RenderWindow* window = nullptr;

        Paddle paddle;
        Ball ball;
        sf::Texture paddleTexture;
        sf::Texture ballTexture;

        void checkBallPaddleCollision();
        void checkBallOutOfBounds();
    };
}
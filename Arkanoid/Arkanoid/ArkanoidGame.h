#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include <vector>
#include "Brick.h"

namespace ArkanoidGame
{
    class ArkanoidGame
    {
    public:
        void Init(sf::RenderWindow& window);
        void Update(float deltaTime);
        void Draw();
        bool IsBallOutOfBounds() const;
        bool IsWin() const;

    private:
        sf::RenderWindow* window = nullptr;

        Paddle paddle;
        Ball ball;
        sf::Texture paddleTexture;
        sf::Texture ballTexture;
        std::vector<Brick> bricks;
        sf::Texture brickTexture;

        void checkBallPaddleCollision();
        void checkBallBrickCollisions();
        void checkBallOutOfBounds();
    };
}
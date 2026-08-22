#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

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
        std::vector<std::shared_ptr<Block>>blocks;

        void checkBallPaddleCollision();
        void checkBallBlockCollisions();
    };
}
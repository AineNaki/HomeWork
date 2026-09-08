#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bonus.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "GameMemento.h"

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
        bool IsGameOver() const { return lives <= 0; }
        std::vector<std::shared_ptr<Block>>& GetBlocks() { return blocks; }
        int GetBreakableBlocksCount() const;

        GameMemento SaveState() const;
        void RestoreState(const GameMemento& memento);
        int GetLives() const { return lives; }
        float GetBonusTimer() const { return bonusTimer; }

    private:
        sf::RenderWindow* window = nullptr;
        std::vector<std::shared_ptr<Block>> blocks;
        Paddle paddle;
        Ball ball;
        sf::Texture paddleTexture;
        sf::Texture ballTexture;
        int lives = 3;
        GameMemento startState{ 3, sf::Vector2f(0.f, 0.f) };
        bool hasStartState = false;

        void checkBallPaddleCollision();
        void checkBallBlockCollisions();

        //Bonus
        std::vector<std::shared_ptr<Bonus>> bonuses;
        float bonusTimer = 0.f;
        std::shared_ptr<Bonus> activeBonus = nullptr;
    };
}
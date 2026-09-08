#include "ArkanoidGame.h"
#include "GameSettings.h"
#include "DurableBlockFactory.h"
#include "SmoothDestroyableBlockFactory.h"
#include "UnbreakableBlock.h"
#include "UnbreakableBlockFactory.h"
#include "GlassBlockFactory.h"
#include "LevelLoader.h"
#include "FireBallBonus.h"
#include "WidePaddleBonus.h"
#include "FragileBlocksBonus.h"


namespace ArkanoidGame
{
    void ArkanoidGame::Init(sf::RenderWindow& window)
    {
        this->window = &window;

        // Paddle texture
        {
            sf::Image img;
            img.create((unsigned int)GameWorld::GetInstance().GetPaddleWidth(),
                (unsigned int)GameWorld::GetInstance().GetPaddleHeight(),
                sf::Color::White);
            paddleTexture.loadFromImage(img);
        }

        // Ball texture (circle)
        {
            float ballSize = GameWorld::GetInstance().GetBallSize();
            sf::RenderTexture renderTex;
            renderTex.create((unsigned int)ballSize, (unsigned int)ballSize);
            renderTex.clear(sf::Color::Transparent);

            sf::CircleShape circle(ballSize / 2.f);
            circle.setFillColor(sf::Color::White);
            renderTex.draw(circle);
            renderTex.display();

            ballTexture = renderTex.getTexture();
        }

        paddle.Init(paddleTexture);
        ball.Init(ballTexture);
        startState = SaveState();
        hasStartState = true;

        LevelLoader levelLoader;
        blocks = levelLoader.LoadLevel(RESOURCES_PATH + "levels.config");
        bonuses.clear();
    }

    void ArkanoidGame::Update(float deltaTime)
    {
        paddle.Update(deltaTime, *window);
        ball.Update(deltaTime);

        for (const auto& block : blocks)
            block->Update(deltaTime);

        checkBallPaddleCollision();
        checkBallBlockCollisions();
        // upd bonus
        for (auto& bonus : bonuses)
            bonus->Update(deltaTime);

        // check
        for (auto& bonus : bonuses)
        {
            if (bonus->IsActive() && paddle.GetBounds().intersects(bonus->GetBounds()))
            {
                bonus->Apply(ball, paddle, blocks);
                activeBonus = bonus;
                bonusTimer = 10.f;
                bonus->Deactivate();
            }
        }

        // Bonus timer
        if (bonusTimer > 0.f)
        {
            bonusTimer -= deltaTime;
            if (bonusTimer <= 0.f && activeBonus)
            {
                activeBonus->Expire(ball, paddle, blocks);
                activeBonus = nullptr;
            }
        }

        if (IsBallOutOfBounds())
        {
            --lives;
            if (lives > 0 && hasStartState)
            {
                RestoreState(startState);
            }
        }
    }

    GameMemento ArkanoidGame::SaveState() const
    {
        return GameMemento(lives, ball.GetPosition());
    }

    void ArkanoidGame::RestoreState(const GameMemento& memento)
    {
        ball.SetPositionX(memento.GetBallPosition().x);
        ball.SetPositionY(memento.GetBallPosition().y);
    }

    void ArkanoidGame::Draw()
    {
        paddle.Draw(*window);
        ball.Draw(*window);

        for (const auto& block : blocks)
            block->Draw(*window);

        // Бонусы
        for (const auto& bonus : bonuses)
            bonus->Draw(*window);
    }

    void ArkanoidGame::checkBallPaddleCollision()
    {
        // Check if ball intersects the paddle
        if (!ball.GetBounds().intersects(paddle.GetBounds()))
            return;

        // Calculate horizontal offset from paddle center
        float paddleCenter = paddle.GetPosition().x;
        float ballX = ball.GetPosition().x;
        float offset = ballX - paddleCenter;  // negative = left, positive = right

        // Normalize offset to [-1, 1] range
        float maxOffset = GameWorld::GetInstance().GetPaddleWidth() / 2.f;
        float factor = offset / maxOffset;
        if (factor < -1.f) factor = -1.f;
        if (factor > 1.f)  factor = 1.f;

        // Maximum bounce angle from vertical (in radians)
        float maxAngle = 60.f * 3.14159f / 180.f;
        float angle = factor * maxAngle;

        // Preserve ball speed, change only direction
        float currentSpeed = std::sqrt(ball.GetVelocityX() * ball.GetVelocityX() +
            ball.GetVelocityY() * ball.GetVelocityY());

        // Calculate new velocity based on hit position
        float newVx = currentSpeed * std::sin(angle);
        float newVy = -currentSpeed * std::cos(angle);  // negative = upwards

        ball.SetVelocity(newVx, newVy);

        // Prevent ball from sticking inside the paddle
        float paddleHeight = GameWorld::GetInstance().GetPaddleHeight();
        float ballSize = GameWorld::GetInstance().GetBallSize();
        ball.SetPositionY(paddle.GetPosition().y - paddleHeight / 2.f - ballSize / 2.f);
    }

    void ArkanoidGame::checkBallBlockCollisions()
    {
        // Prevent multiple collisions in the same frame
        bool ballCollidedThisFrame = false;

        for (auto& block : blocks)
        {
            // Only one collision per frame
            if (ballCollidedThisFrame)
                break;

            // Skip already destroyed blocks
            if (block->IsDestroyed())
                continue;

            // Check intersection between ball and block
            if (!ball.GetBounds().intersects(block->GetBounds()))
                continue;

            // Let the block handle the hit (each type reacts differently)
            block->Hit();
            //bonus chance
            if (block->IsDestroyed())
            {
                if (rand() % 100 < 10)  // 10% шанс
                {
                    int type = rand() % 3;
                    if (type == 0)
                        bonuses.push_back(std::make_shared<FireBallBonus>(sf::Vector2f(block->GetBounds().left, block->GetBounds().top)));
                    else if (type == 1)
                        bonuses.push_back(std::make_shared<WidePaddleBonus>(sf::Vector2f(block->GetBounds().left, block->GetBounds().top)));
                    else
                        bonuses.push_back(std::make_shared<FragileBlocksBonus>(sf::Vector2f(block->GetBounds().left, block->GetBounds().top)));
                }
            }

            // Glass blocks don't bounce the ball
            if (!block->ShouldBounceBall())
                continue;
            // Fire ball doesn't bounce — it flies through blocks
            if (ball.IsFireMode())
                continue;

            ballCollidedThisFrame = true;

            sf::FloatRect ballBounds = ball.GetBounds();
            sf::FloatRect blockBounds = block->GetBounds();

            // Ball edges
            float ballBottom = ballBounds.top + ballBounds.height;
            float ballTop = ballBounds.top;
            float ballLeft = ballBounds.left;
            float ballRight = ballBounds.left + ballBounds.width;

            // Block edges
            float blockBottom = blockBounds.top + blockBounds.height;
            float blockTop = blockBounds.top;
            float blockLeft = blockBounds.left;
            float blockRight = blockBounds.left + blockBounds.width;

            // Overlap along each axis
            float overlapBottom = ballBottom - blockTop;   // ball entered from below
            float overlapTop = blockBottom - ballTop;      // ball entered from above
            float overlapLeft = ballRight - blockLeft;     // ball entered from left
            float overlapRight = blockRight - ballLeft;    // ball entered from right

            // Find the smallest overlap — that's the side of impact
            float minOverlap = std::min(std::min(overlapBottom, overlapTop),
                std::min(overlapLeft, overlapRight));

            float ballSize = GameWorld::GetInstance().GetBallSize();

            if (minOverlap == overlapBottom || minOverlap == overlapTop)
            {
                // Hit from top or bottom
                ball.BounceY();

                // Push the ball out of the block to prevent sticking
                if (minOverlap == overlapBottom)
                    ball.SetPositionY(blockTop - ballSize / 2.f);
                else
                    ball.SetPositionY(blockBottom + ballSize / 2.f);
            }
            else
            {
                // Hit from left or right
                ball.BounceX();

                // Push the ball out of the block to prevent sticking
                if (minOverlap == overlapLeft)
                    ball.SetPositionX(blockLeft - ballSize / 2.f);
                else
                    ball.SetPositionX(blockRight + ballSize / 2.f);
            }
        }
    }

    bool ArkanoidGame::IsBallOutOfBounds() const
    {
        return ball.GetPosition().y > GameWorld::GetInstance().GetScreenHeight() + GameWorld::GetInstance().GetBallSize();
    }

    bool ArkanoidGame::IsWin() const
    {
        for (const auto& block : blocks)
        {
            // Skip unbreakable blocks
            if (dynamic_cast<UnbreakableBlock*>(block.get()) != nullptr)
                continue;

            if (!block->IsDestroyed())
                return false;
        }
        return true;
    }
    int ArkanoidGame::GetBreakableBlocksCount() const
    {
        int count = 0;
        for (const auto& block : blocks)
        {
          
            if (dynamic_cast<UnbreakableBlock*>(block.get()) != nullptr)
                continue;

            ++count;
        }
        return count;
    }
}
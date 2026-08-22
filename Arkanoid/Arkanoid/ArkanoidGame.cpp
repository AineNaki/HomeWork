#include "ArkanoidGame.h"
#include "Constants.h"
#include "UnbreakableBlock.h"
#include "SmoothDestroyableBlock.h"
#include "DurableBlock.h"
#include "GlassBlock.h"

namespace ArkanoidGame
{
    void ArkanoidGame::Init(sf::RenderWindow& window)
    {
        this->window = &window;

        // Paddle texture
        {
            sf::Image img;
            img.create((unsigned int)PADDLE_WIDTH, (unsigned int)PADDLE_HEIGHT, sf::Color::White);
            paddleTexture.loadFromImage(img);
        }

        // Ball texture (circle)
        {
            sf::RenderTexture renderTex;
            renderTex.create((unsigned int)BALL_SIZE, (unsigned int)BALL_SIZE);
            renderTex.clear(sf::Color::Transparent);

            sf::CircleShape circle(BALL_SIZE / 2.f);
            circle.setFillColor(sf::Color::White);
            renderTex.draw(circle);
            renderTex.display();

            ballTexture = renderTex.getTexture();
        }

        paddle.Init(paddleTexture);
        ball.Init(ballTexture);
        // 20 blocks: 2 rows of 10
        blocks.clear();
        for (int i = 0; i < 18; ++i)
        {
            int row = i / 6;              // 0, 1, 2
            int col = i % 6;              // 0..5
            float x = 100.f + col * 110.f;
            float y = 80.f + row * 45.f;

            if (i == 2 || i == 7 || i == 12)
                blocks.push_back(std::make_shared<UnbreakableBlock>(sf::Vector2f(x, y)));
            else if (i == 5 || i == 15)
                blocks.push_back(std::make_shared<GlassBlock>(sf::Vector2f(x, y)));
            else if (i % 2 == 0)
                blocks.push_back(std::make_shared<SmoothDestroyableBlock>(sf::Vector2f(x, y)));
            else
                blocks.push_back(std::make_shared<DurableBlock>(sf::Vector2f(x, y)));
        }
    }

    void ArkanoidGame::Update(float deltaTime)
    {
        paddle.Update(deltaTime, *window);
        ball.Update(deltaTime);

        for (const auto& block : blocks)
            block->Update(deltaTime);

        checkBallPaddleCollision();
        checkBallBlockCollisions();
    }

    void ArkanoidGame::Draw()
    {
        paddle.Draw(*window);
        ball.Draw(*window);
        for (const auto& block : blocks)
            block->Draw(*window);
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
        float maxOffset = PADDLE_WIDTH / 2.f;
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
        ball.SetPositionY(paddle.GetPosition().y - PADDLE_HEIGHT / 2.f - BALL_SIZE / 2.f);
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

            // Glass blocks don't bounce the ball
            if (!block->ShouldBounceBall())
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

            if (minOverlap == overlapBottom || minOverlap == overlapTop)
            {
                // Hit from top or bottom
                ball.BounceY();

                // Push the ball out of the block to prevent sticking
                if (minOverlap == overlapBottom)
                    ball.SetPositionY(blockTop - BALL_SIZE / 2.f);
                else
                    ball.SetPositionY(blockBottom + BALL_SIZE / 2.f);
            }
            else
            {
                // Hit from left or right
                ball.BounceX();

                // Push the ball out of the block to prevent sticking
                if (minOverlap == overlapLeft)
                    ball.SetPositionX(blockLeft - BALL_SIZE / 2.f);
                else
                    ball.SetPositionX(blockRight + BALL_SIZE / 2.f);
            }
        }
    }

    bool ArkanoidGame::IsBallOutOfBounds() const
    {
        return ball.GetPosition().y > SCREEN_HEIGHT + BALL_SIZE;
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
}
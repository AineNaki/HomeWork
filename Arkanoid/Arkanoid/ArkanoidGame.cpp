#include "ArkanoidGame.h"
#include "Constants.h"

namespace ArkanoidGame
{
    void ArkanoidGame::Init(sf::RenderWindow& window)
    {
        this->window = &window;

        {
            sf::Image img;
            img.create((unsigned int)PADDLE_WIDTH, (unsigned int)PADDLE_HEIGHT, sf::Color::White);
            paddleTexture.loadFromImage(img);
        }

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
        sf::Image img;
        img.create((unsigned int)BRICK_WIDTH, (unsigned int)BRICK_HEIGHT, sf::Color(200, 100, 50));
        brickTexture.loadFromImage(img);
        bricks.clear();
        for (int i = 0; i < BRICK_COUNT; ++i)
        {
            Brick brick;
            int row = i / 5;            
            int col = i % 5;            
            float x = 100.f + col * (BRICK_WIDTH + 10.f);
            float y = 100.f + row * (BRICK_HEIGHT + 10.f);
            brick.Init(brickTexture, x, y);
            bricks.push_back(brick);
        }
    }

    void ArkanoidGame::Update(float deltaTime)
    {
        paddle.Update(deltaTime, *window);
        ball.Update(deltaTime);

        checkBallPaddleCollision();
        checkBallBrickCollisions();
    }

    void ArkanoidGame::Draw()
    {
        paddle.Draw(*window);
        ball.Draw(*window);
        for (auto& brick : bricks)
            brick.Draw(*window);
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

    void ArkanoidGame::checkBallBrickCollisions()
    {
        for (auto& brick : bricks)
        {
            if (brick.IsDestroyed())
                continue;

            sf::FloatRect ballBounds = ball.GetBounds();
            sf::FloatRect brickBounds = brick.GetBounds();

            if (!ballBounds.intersects(brickBounds))
                continue;

            brick.Destroy();

            // ќпредел€ем, с какой стороны ударилс€ м€ч
            float ballBottom = ballBounds.top + ballBounds.height;
            float ballTop = ballBounds.top;
            float ballLeft = ballBounds.left;
            float ballRight = ballBounds.left + ballBounds.width;

            float brickBottom = brickBounds.top + brickBounds.height;
            float brickTop = brickBounds.top;
            float brickLeft = brickBounds.left;
            float brickRight = brickBounds.left + brickBounds.width;

            // ѕересечени€ по ос€м
            float overlapBottom = ballBottom - brickTop;  
            float overlapTop = brickBottom - ballTop;     
            float overlapLeft = ballRight - brickLeft;    
            float overlapRight = brickRight - ballLeft;   

            // Ќаходим минимальное пересечение Ч с этой стороны и ударилс€
            float minOverlap = std::min(std::min(overlapBottom, overlapTop),
                std::min(overlapLeft, overlapRight));

            if (minOverlap == overlapBottom || minOverlap == overlapTop)
                ball.BounceY(); 
            else
                ball.BounceX();  

            break;  
        }
    }

    bool ArkanoidGame::IsBallOutOfBounds() const
    {
        return ball.GetPosition().y > SCREEN_HEIGHT + BALL_SIZE;
    }

    bool ArkanoidGame::IsWin() const
    {
        for (const auto& brick : bricks)
            if (!brick.IsDestroyed())
                return false;
        return true;
    }
}
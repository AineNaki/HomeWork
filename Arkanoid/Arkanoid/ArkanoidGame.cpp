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
    }

    void ArkanoidGame::Update(float deltaTime)
    {
        paddle.Update(deltaTime, *window);
        ball.Update(deltaTime);

        checkBallPaddleCollision();
        checkBallOutOfBounds();
    }

    void ArkanoidGame::Draw()
    {
        paddle.Draw(*window);
        ball.Draw(*window);
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

    void ArkanoidGame::checkBallOutOfBounds()
    {
        if (ball.GetPosition().y > SCREEN_HEIGHT + BALL_SIZE)
        {
            ball.Init(ballTexture);
        }
    }
}
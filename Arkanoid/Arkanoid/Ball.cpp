#include "Ball.h"
#include "Math.h"
#include "GameSettings.h"
#include <cmath>

namespace ArkanoidGame
{
    void Ball::Init(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        SetSpriteSize(sprite,
            GameWorld::GetInstance().GetBallSize(),
            GameWorld::GetInstance().GetBallSize());
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);

        position.x = GameWorld::GetInstance().GetScreenWidth() / 2.f;
        position.y = GameWorld::GetInstance().GetScreenHeight() / 2.f;

        float speed = GameWorld::GetInstance().GetBallSpeed();
        float angle = 45.f * 3.14159f / 180.f;
        velocity.x = speed * std::cos(angle);
        velocity.y = speed * std::sin(angle);

        sprite.setPosition(position);
    }

    void Ball::Update(float deltaTime)
    {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        float ballSize = GameWorld::GetInstance().GetBallSize();
        float screenWidth = GameWorld::GetInstance().GetScreenWidth();
        float screenHeight = GameWorld::GetInstance().GetScreenHeight();

        if (position.x - ballSize / 2.f < 0.f)
        {
            position.x = ballSize / 2.f;
            BounceX();
        }
        if (position.x + ballSize / 2.f > screenWidth)
        {
            position.x = screenWidth - ballSize / 2.f;
            BounceX();
        }
        if (position.y - ballSize / 2.f < 0.f)
        {
            position.y = ballSize / 2.f;
            BounceY();
        }

        sprite.setPosition(position);
    }

    void Ball::Draw(sf::RenderWindow& window) const
    {
        window.draw(sprite);
    }

    sf::FloatRect Ball::GetBounds() const
    {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f Ball::GetPosition() const
    {
        return position;
    }

    void Ball::BounceX()
    {
        velocity.x = -velocity.x;
    }

    void Ball::BounceY()
    {
        velocity.y = -velocity.y;
    }
}
#include "Ball.h"
#include "Math.h"
#include <cmath>

namespace ArkanoidGame
{
    void Ball::Init(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        SetSpriteSize(sprite, BALL_SIZE, BALL_SIZE);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);

        position.x = SCREEN_WIDTH / 2.f;
        position.y = SCREEN_HEIGHT / 2.f;


        float angle = 45.f * 3.14159f / 180.f;
        velocity.x = speed * std::cos(angle);
        velocity.y = speed * std::sin(angle);

        sprite.setPosition(position);
    }

    void Ball::Update(float deltaTime)
    {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        if (position.x - BALL_SIZE / 2.f < 0.f)
        {
            position.x = BALL_SIZE / 2.f;
            BounceX();
        }
        if (position.x + BALL_SIZE / 2.f > SCREEN_WIDTH)
        {
            position.x = SCREEN_WIDTH - BALL_SIZE / 2.f;
            BounceX();
        }
        if (position.y - BALL_SIZE / 2.f < 0.f)
        {
            position.y = BALL_SIZE / 2.f;
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
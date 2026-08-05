#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ArkanoidGame
{
    class Ball
    {
    public:
        void Init(const sf::Texture& texture);
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window) const;
        sf::FloatRect GetBounds() const;
        sf::Vector2f GetPosition() const;
        void BounceX();
        void BounceY();
        float GetVelocityX() const { return velocity.x; }
        float GetVelocityY() const { return velocity.y; }
        void SetVelocity(float vx, float vy) { velocity.x = vx; velocity.y = vy; }
        void SetPositionY(float y) { position.y = y; sprite.setPosition(position); }

    private:
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Vector2f velocity;
        float speed = BALL_SPEED;
    };

}

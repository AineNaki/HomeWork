#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Constants.h"

namespace ArkanoidGame
{
    class Ball : public GameObject
    {
    public:
        void Init(const sf::Texture& texture);
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) const override;
        sf::FloatRect GetBounds() const override;
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
#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Constants.h"
#include "GameSettings.h"

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
        // Set ball X position and update sprite immediately
        void SetPositionX(float x) { position.x = x; sprite.setPosition(position); }
        // Set ball Y position and update sprite immediately
        void SetPositionY(float y) { position.y = y; sprite.setPosition(position); }
        //fireball
        void SetFireMode(bool fire)
        {
            fireMode = fire;
            sprite.setColor(fire ? sf::Color(255, 100, 0) : sf::Color::White);
        }
        bool IsFireMode() const { return fireMode; }

    private:
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Vector2f velocity;
        float speed = 0.f;
        bool fireMode = false;
    };
}
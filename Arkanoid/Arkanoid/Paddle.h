#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Constants.h"

namespace ArkanoidGame
{
    class Paddle : public GameObject
    {
    public:
        void Init(const sf::Texture& texture);
        void Update(float deltaTime, const sf::RenderWindow& window);
        void Draw(sf::RenderWindow& window) const override;
        sf::FloatRect GetBounds() const override;
        sf::Vector2f GetPosition() const;

    private:
        sf::Sprite sprite;
        sf::Vector2f position;
        float speed = PADDLE_SPEED;
    };
}
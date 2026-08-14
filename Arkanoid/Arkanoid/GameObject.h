#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    class GameObject
    {
    public:
        virtual ~GameObject() = default;
        virtual void Draw(sf::RenderWindow& window) const = 0;
        virtual sf::FloatRect GetBounds() const = 0;
        virtual bool IsDestroyed() const { return false; }
        virtual void Update(float deltaTime) {}
    };
}
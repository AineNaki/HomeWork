#include "Bonus.h"
#include "Math.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    Bonus::Bonus(const sf::Vector2f& position)
        : position(position)
    {
    }

    void Bonus::Update(float deltaTime)
    {
        if (!active) return;

        position.y += fallSpeed * deltaTime;
        sprite.setPosition(position);
    }

    void Bonus::Draw(sf::RenderWindow& window) const
    {
        if (active)
            window.draw(sprite);
    }

    sf::FloatRect Bonus::GetBounds() const
    {
        return sprite.getGlobalBounds();
    }
}
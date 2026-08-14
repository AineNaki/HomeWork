#include "Brick.h"
#include "Math.h"

namespace ArkanoidGame
{
    void Brick::Init(const sf::Texture& texture, float x, float y)
    {
        sprite.setTexture(texture);
        SetSpriteSize(sprite, BRICK_WIDTH, BRICK_HEIGHT);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);

        position.x = x;
        position.y = y;
        sprite.setPosition(position);
    }

    void Brick::Draw(sf::RenderWindow& window) const
    {
        if (!destroyed)
            window.draw(sprite);
    }

    sf::FloatRect Brick::GetBounds() const
    {
        return sprite.getGlobalBounds();
    }
}
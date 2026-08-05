#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
    {
        const sf::Texture* texture = sprite.getTexture();
        if (texture) {
            sf::Vector2u textureSize = texture->getSize();
            float scaleX = desiredWidth / textureSize.x;
            float scaleY = desiredHeight / textureSize.y;
            sprite.setScale(scaleX, scaleY);
        }
    }

    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
    {
        sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
    }
}
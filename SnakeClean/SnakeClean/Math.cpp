#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight, float marginX, float marginY)
	{
		Position2D result;
		result.x = marginX + rand() / (float)RAND_MAX * (screenWidth - 2 * marginX);
		result.y = marginY + rand() / (float)RAND_MAX * (screenHeight - 2 * marginY);
		return result;
	}

    bool IsCollide(Position2D pos1, float size1, Position2D pos2, float size2)
    {
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        float squareDistance = dx * dx + dy * dy;
        float squareRadiusSum = (size1 + size2) * (size1 + size2) / 4.f;
        return squareDistance <= squareRadiusSum;
    }

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
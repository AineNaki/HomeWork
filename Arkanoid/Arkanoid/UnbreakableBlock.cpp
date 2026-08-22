#include "UnbreakableBlock.h"

namespace ArkanoidGame
{
    UnbreakableBlock::UnbreakableBlock(const sf::Vector2f& position)
        : Block(position, sf::Color::Red)
    {
        sf::Image img;
        img.create((unsigned int)BLOCK_WIDTH, (unsigned int)BLOCK_HEIGHT, color);
        texture.loadFromImage(img);

        sprite.setTexture(texture);
        SetSpriteSize(sprite, BLOCK_WIDTH, BLOCK_HEIGHT);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position);
    }
}
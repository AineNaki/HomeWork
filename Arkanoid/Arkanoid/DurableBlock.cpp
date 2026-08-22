#include "DurableBlock.h"

namespace ArkanoidGame
{
    DurableBlock::DurableBlock(const sf::Vector2f& position)
        : Block(position, sf::Color::Blue)
    {
        sf::Image img;
        img.create((unsigned int)BLOCK_WIDTH, (unsigned int)BLOCK_HEIGHT, sf::Color::White);
        texture.loadFromImage(img);

        sprite.setTexture(texture);
        SetSpriteSize(sprite, BLOCK_WIDTH, BLOCK_HEIGHT);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position);
        sprite.setColor(color);  
    }

    void DurableBlock::OnHit()
    {
        --hitCount;
        if (hitCount <= 0)
        {
            destroyed = true;
        }
        else
        {
            UpdateColor();
        }
    }

    void DurableBlock::UpdateColor()
    {
        if (hitCount == 2)
            sprite.setColor(sf::Color(100, 150, 255));   
        else if (hitCount == 1)
            sprite.setColor(sf::Color(180, 210, 255));  
    }
}
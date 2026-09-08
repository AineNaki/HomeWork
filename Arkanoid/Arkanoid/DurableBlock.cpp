#include "DurableBlock.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    DurableBlock::DurableBlock(const sf::Vector2f& position)
        : Block(position, sf::Color::Blue)
    {
        sf::Image img;
        img.create((unsigned int)GameWorld::GetInstance().GetBlockWidth(),
            (unsigned int)GameWorld::GetInstance().GetBlockHeight(),
            sf::Color::White);
        texture.loadFromImage(img);

        sprite.setTexture(texture);
        SetSpriteSize(sprite,
            GameWorld::GetInstance().GetBlockWidth(),
            GameWorld::GetInstance().GetBlockHeight());
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position);
        sprite.setColor(color);
    }

    void DurableBlock::OnHit()
    {
        --hitCount;
        if (hitCount <= 0)
        {
            Destroy();
        }
        else
        {
            UpdateColor();
        }
    }

    void DurableBlock::UpdateColor()
    {
        if (hitCount == 2)
            sprite.setColor(sf::Color(100, 150, 255));   // light blue
        else if (hitCount == 1)
            sprite.setColor(sf::Color(180, 210, 255));   // pale blue
    }
}
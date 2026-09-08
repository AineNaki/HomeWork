#include "UnbreakableBlock.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    UnbreakableBlock::UnbreakableBlock(const sf::Vector2f& position)
        : Block(position, sf::Color::Red)
    {
        sf::Image img;
        img.create((unsigned int)GameWorld::GetInstance().GetBlockWidth(),
            (unsigned int)GameWorld::GetInstance().GetBlockHeight(),
            color);
        texture.loadFromImage(img);

        sprite.setTexture(texture);
        SetSpriteSize(sprite,
            GameWorld::GetInstance().GetBlockWidth(),
            GameWorld::GetInstance().GetBlockHeight());
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position);
    }
}
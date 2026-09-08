#include "GlassBlock.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    GlassBlock::GlassBlock(const sf::Vector2f& position)
        : Block(position, sf::Color(255, 255, 255, 100))
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

    void GlassBlock::OnHit()
    {
        Destroy();
    }

    bool GlassBlock::ShouldBounceBall() const
    {
        return false;
    }
}
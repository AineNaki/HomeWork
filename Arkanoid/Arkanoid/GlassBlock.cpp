#include "GlassBlock.h"

namespace ArkanoidGame
{
    GlassBlock::GlassBlock(const sf::Vector2f& position)
        : Block(position, sf::Color(255, 255, 255, 100))
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

    void GlassBlock::OnHit()
    {
        destroyed = true;
    }

    bool GlassBlock::ShouldBounceBall() const
    {
        return false;
    }
}
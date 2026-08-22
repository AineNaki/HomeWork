#include "SmoothDestroyableBlock.h"

namespace ArkanoidGame
{
    SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position)
        : Block(position, sf::Color::Green)
    {
        sf::Image img;
        img.create((unsigned int)BLOCK_WIDTH, (unsigned int)BLOCK_HEIGHT, color);
        texture.loadFromImage(img);
        sprite.setTexture(texture);
        SetSpriteSize(sprite, BLOCK_WIDTH, BLOCK_HEIGHT);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position);
    }

    void SmoothDestroyableBlock::Update(float deltaTime)
    {
        UpdateTimer(deltaTime);
    }

    bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Collidable> collidableObject) const
    {
        if (isTimerStarted)
            return false;

        auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
        if (!gameObject)
            return false;

        return GetRect().intersects(gameObject->GetBounds());
    }

    void SmoothDestroyableBlock::OnHit()
    {
        if (!isTimerStarted)
            StartTimer(BREAK_DELAY);
    }

    void SmoothDestroyableBlock::FinalAction()
    {
        destroyed = true;
    }

    void SmoothDestroyableBlock::EachTickAction(float deltaTime)
    {
        // Gradually make the block transparent
        float alpha = 255.f * currentTime / destroyTime;
        sf::Color newColor = color;
        newColor.a = (sf::Uint8)alpha;
        sprite.setColor(newColor);
    }
}
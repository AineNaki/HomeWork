#include "Block.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    Block::Block(const sf::Vector2f& position, const sf::Color& color)
        : position(position), color(color)
    {
    }

    void Block::Draw(sf::RenderWindow& window) const
    {
        if (!destroyed)
            window.draw(sprite);
    }

    sf::FloatRect Block::GetBounds() const
    {
        return sprite.getGlobalBounds();
    }

    sf::FloatRect Block::GetRect() const
    {
        return sprite.getGlobalBounds();
    }

    bool Block::GetCollision(std::shared_ptr<Collidable> other) const
    {
        if (destroyed)
            return false;

        auto gameObject = std::dynamic_pointer_cast<GameObject>(other);
        if (!gameObject)
            return false;

        return GetRect().intersects(gameObject->GetBounds());
    }



    void Block::Destroy()
    {
        if (!destroyed)
        {
            destroyed = true;
            Emit();  
        }
    }
}
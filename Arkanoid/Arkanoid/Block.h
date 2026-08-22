#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame
{
    class Block : public GameObject, public Collidable
    {
    protected:
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Color color;
        bool destroyed = false;
        sf::Texture texture;

        virtual void OnHit() = 0;

    public:
        Block(const sf::Vector2f& position, const sf::Color& color);
        virtual ~Block() = default;

        void Draw(sf::RenderWindow& window) const override;
        sf::FloatRect GetBounds() const override;
        bool IsDestroyed() const override;

        sf::FloatRect GetRect() const override;
        bool GetCollision(std::shared_ptr<Collidable> other) const override;
        void Hit() { if (!destroyed) OnHit(); }
        virtual bool ShouldBounceBall() const { return true; }
    };
}
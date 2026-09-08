#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "IObservable.h"
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <memory>


namespace ArkanoidGame
{
    class Block : public GameObject, public Collidable, public IObservable
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
        bool IsDestroyed() const override { return destroyed; }

        sf::FloatRect GetRect() const override;
        bool GetCollision(std::shared_ptr<Collidable> other) const override;
        void Destroy();
        void Hit()
        {
            if (!destroyed)
            {
                if (fragileMode)
                {
                    Destroy(); 
                }
                else
                {
                    OnHit();
                }
            }
        }
        virtual bool ShouldBounceBall() const { return true; }
        virtual int GetScore() const { return 0; }
        //mode
        void SetFragileMode(bool fragile)
        {
            fragileMode = fragile;
            sprite.setColor(fragile ? sf::Color(255, 200, 200) : sf::Color::White);
        }
        bool IsFragileMode() const { return fragileMode; }
    private:
        bool fragileMode = false;
    };
}
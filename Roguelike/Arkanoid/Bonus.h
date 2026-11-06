#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace Roguelike
{
    class Ball;
    class Paddle;
    class Block;

    class Bonus
    {
    public:
        Bonus(const sf::Vector2f& position);
        virtual ~Bonus() = default;

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window) const;
        sf::FloatRect GetBounds() const;

        bool IsActive() const { return active; }
        void Deactivate() { active = false; }

        virtual void Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) = 0;
        virtual void Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) = 0;

    protected:
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Texture texture;
        bool active = true;
        float fallSpeed = 100.f;
    };
}
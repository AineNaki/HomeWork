#include "FragileBlocksBonus.h"
#include "Block.h"

namespace ArkanoidGame
{
    FragileBlocksBonus::FragileBlocksBonus(const sf::Vector2f& position)
        : Bonus(position)
    {
        sf::RenderTexture renderTex;
        renderTex.create(20, 20);
        renderTex.clear(sf::Color::Transparent);

        sf::CircleShape circle(10.f);
        circle.setFillColor(sf::Color(200, 100, 255));
        renderTex.draw(circle);
        renderTex.display();

        texture = renderTex.getTexture();
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void FragileBlocksBonus::Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        for (auto& block : blocks)
        {
            block->SetFragileMode(true);
        }
    }

    void FragileBlocksBonus::Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        for (auto& block : blocks)
        {
            block->SetFragileMode(false);
        }
    }
}
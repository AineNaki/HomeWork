#include "FireBallBonus.h"
#include "Ball.h"
#include "Block.h"
#include <vector>

namespace ArkanoidGame
{
    FireBallBonus::FireBallBonus(const sf::Vector2f& position)
        : Bonus(position)
    {
        sf::RenderTexture renderTex;
        renderTex.create(20, 20);
        renderTex.clear(sf::Color::Transparent);

        sf::CircleShape circle(10.f);
        circle.setFillColor(sf::Color(255, 100, 0));
        renderTex.draw(circle);
        renderTex.display();

        texture = renderTex.getTexture();
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void FireBallBonus::Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        ball.SetFireMode(true); 
    }

    void FireBallBonus::Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        ball.SetFireMode(false); 
    }
}
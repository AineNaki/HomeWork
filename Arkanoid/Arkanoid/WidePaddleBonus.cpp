#include "WidePaddleBonus.h"
#include "Paddle.h"

namespace ArkanoidGame
{
    WidePaddleBonus::WidePaddleBonus(const sf::Vector2f& position)
        : Bonus(position)
    {
        sf::RenderTexture renderTex;
        renderTex.create(20, 20);
        renderTex.clear(sf::Color::Transparent);

        sf::CircleShape circle(10.f);
        circle.setFillColor(sf::Color(100, 200, 255));
        renderTex.draw(circle);
        renderTex.display();

        texture = renderTex.getTexture();
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void WidePaddleBonus::Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        paddle.SetWideMode(true);  //  расширяем
    }

    void WidePaddleBonus::Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks)
    {
        paddle.SetWideMode(false);  // сужаем обратно
    }
}
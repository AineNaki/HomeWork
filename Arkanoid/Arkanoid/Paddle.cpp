#include "Paddle.h"
#include "Math.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    void Paddle::Init(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        SetSpriteSize(sprite,
            GameWorld::GetInstance().GetPaddleWidth(),
            GameWorld::GetInstance().GetPaddleHeight());
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);

        position.x = GameWorld::GetInstance().GetScreenWidth() / 2.f;
        position.y = GameWorld::GetInstance().GetScreenHeight()
            - GameWorld::GetInstance().GetPaddleHeight() - 10.f;
        sprite.setPosition(position);
    }

    void Paddle::Update(float deltaTime, const sf::RenderWindow& window)
    {
        // Mouse control (takes priority over keyboard)
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        position.x = (float)mousePos.x;

        bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        float speed = GameWorld::GetInstance().GetPaddleSpeed();

        if (leftPressed)
            position.x -= speed * deltaTime;
        if (rightPressed)
            position.x += speed * deltaTime;

        float halfWidth = GameWorld::GetInstance().GetPaddleWidth() / 2.f;
        float screenWidth = GameWorld::GetInstance().GetScreenWidth();

        if (position.x - halfWidth < 0.f)
            position.x = halfWidth;
        if (position.x + halfWidth > screenWidth)
            position.x = screenWidth - halfWidth;

        // Wide mode scale
        float scaleX = wideMode ? 1.5f : 1.f;
        sprite.setScale(scaleX, 1.f);

        sprite.setPosition(position);
    }

    void Paddle::Draw(sf::RenderWindow& window) const
    {
        window.draw(sprite);
    }

    sf::FloatRect Paddle::GetBounds() const
    {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f Paddle::GetPosition() const
    {
        return position;
    }
}
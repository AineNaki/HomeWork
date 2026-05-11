#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, const sf::Texture& texture)
    {
        apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT, APPLE_SIZE / 2, APPLE_SIZE / 2);

        apple.sprite.setTexture(texture);
        SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);   
        SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);     
        apple.sprite.setPosition(apple.position.x, apple.position.y);

        //Choose a random color index (0 = green, 1 = red, 2 = yellow) for visual variety
        int colorChoice = rand() % 3;
        switch (colorChoice)
        {
        case 0:
            apple.sprite.setColor(sf::Color::Green);
            break;
        case 1:
            apple.sprite.setColor(sf::Color::Red);
            break;
        case 2:
            apple.sprite.setColor(sf::Color::Yellow);
            break;
        }
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.x, apple.position.y);
        window.draw(apple.sprite);
    }
}
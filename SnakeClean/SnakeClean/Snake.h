#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
    enum class SnakeDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Snake
    {
        std::deque<Position2D> body;

        SnakeDirection direction = SnakeDirection::Right;
        SnakeDirection nextDirection = SnakeDirection::Right;

        float speed = INITIAL_SPEED;
        float timeSinceLastMove = 0.f;

        sf::Sprite headRight;
        sf::Sprite headUp;
        sf::Sprite headLeft;
        sf::Sprite headDown;

        sf::Sprite bodyHorizontal;
        sf::Sprite bodyVertical;

        sf::Sprite bodyTopLeft;      
        sf::Sprite bodyTopRight;     
        sf::Sprite bodyBottomLeft;   
        sf::Sprite bodyBottomRight;  

        sf::Sprite tailRight;
        sf::Sprite tailUp;
        sf::Sprite tailLeft;
        sf::Sprite tailDown;
    };

    void InitSnake(Snake& snake,
        const sf::Texture& headRightTex, const sf::Texture& headUpTex,
        const sf::Texture& headLeftTex, const sf::Texture& headDownTex,
        const sf::Texture& bodyHorizontalTex, const sf::Texture& bodyVerticalTex,
        const sf::Texture& bodyTopLeftTex, const sf::Texture& bodyTopRightTex,
        const sf::Texture& bodyBottomLeftTex, const sf::Texture& bodyBottomRightTex,
        const sf::Texture& tailRightTex, const sf::Texture& tailUpTex,
        const sf::Texture& tailLeftTex, const sf::Texture& tailDownTex);

    void UpdateSnake(Snake& snake, float deltaTime);
    void DrawSnake(Snake& snake, sf::RenderWindow& window);
    void SetSnakeDirection(Snake& snake, SnakeDirection newDirection);
}
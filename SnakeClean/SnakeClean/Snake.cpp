#include "Snake.h"

namespace SnakeGame
{
    void InitSnake(Snake& snake,
        const sf::Texture& headRightTex, const sf::Texture& headUpTex,
        const sf::Texture& headLeftTex, const sf::Texture& headDownTex,
        const sf::Texture& bodyHorizontalTex, const sf::Texture& bodyVerticalTex,
        const sf::Texture& bodyTopLeftTex, const sf::Texture& bodyTopRightTex,
        const sf::Texture& bodyBottomLeftTex, const sf::Texture& bodyBottomRightTex,
        const sf::Texture& tailRightTex, const sf::Texture& tailUpTex,
        const sf::Texture& tailLeftTex, const sf::Texture& tailDownTex)
    {
        float startX = (GRID_WIDTH / 2) * CELL_SIZE;
        float startY = (GRID_HEIGHT / 2) * CELL_SIZE;

        snake.body.clear();
        for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i)
        {
            Position2D segment;
            segment.x = startX - i * CELL_SIZE;
            segment.y = startY;
            snake.body.push_back(segment);
        }

        snake.direction = SnakeDirection::Right;
        snake.nextDirection = SnakeDirection::Right;
        snake.speed = INITIAL_SPEED;
        snake.timeSinceLastMove = 0.f;

        auto setupSprite = [](sf::Sprite& sprite, const sf::Texture& texture)
        {
            sprite.setTexture(texture);
            SetSpriteSize(sprite, CELL_SIZE, CELL_SIZE);
            SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        };

        setupSprite(snake.headRight, headRightTex);
        setupSprite(snake.headUp, headUpTex);
        setupSprite(snake.headLeft, headLeftTex);
        setupSprite(snake.headDown, headDownTex);

        setupSprite(snake.bodyHorizontal, bodyHorizontalTex);
        setupSprite(snake.bodyVertical, bodyVerticalTex);

        setupSprite(snake.bodyTopLeft, bodyTopLeftTex);
        setupSprite(snake.bodyTopRight, bodyTopRightTex);
        setupSprite(snake.bodyBottomLeft, bodyBottomLeftTex);
        setupSprite(snake.bodyBottomRight, bodyBottomRightTex);

        setupSprite(snake.tailRight, tailRightTex);
        setupSprite(snake.tailUp, tailUpTex);
        setupSprite(snake.tailLeft, tailLeftTex);
        setupSprite(snake.tailDown, tailDownTex);
    }

    void SetSnakeDirection(Snake& snake, SnakeDirection newDirection)
    {
        if ((snake.direction == SnakeDirection::Right && newDirection == SnakeDirection::Left) ||
            (snake.direction == SnakeDirection::Left && newDirection == SnakeDirection::Right) ||
            (snake.direction == SnakeDirection::Up && newDirection == SnakeDirection::Down) ||
            (snake.direction == SnakeDirection::Down && newDirection == SnakeDirection::Up))
        {
            return; 
        }

        snake.nextDirection = newDirection;
    }

    void UpdateSnake(Snake& snake, float deltaTime)
    {
        snake.timeSinceLastMove += deltaTime;
        float moveInterval = CELL_SIZE / snake.speed;

        if (snake.timeSinceLastMove < moveInterval)
            return;

        snake.timeSinceLastMove -= moveInterval;
        snake.direction = snake.nextDirection;

        Position2D newHead = snake.body.front();

        switch (snake.direction)
        {
        case SnakeDirection::Right: newHead.x += CELL_SIZE; break;
        case SnakeDirection::Up:    newHead.y -= CELL_SIZE; break;
        case SnakeDirection::Left:  newHead.x -= CELL_SIZE; break;
        case SnakeDirection::Down:  newHead.y += CELL_SIZE; break;
        }

        snake.body.push_front(newHead);
        snake.body.pop_back();
    }

    void DrawSnake(Snake& snake, sf::RenderWindow& window)
    {
        for (size_t i = 0; i < snake.body.size(); ++i)
        {
            sf::Sprite* spriteToUse = nullptr;

            if (i == 0)
            {
                switch (snake.direction)
                {
                case SnakeDirection::Right: spriteToUse = &snake.headRight; break;
                case SnakeDirection::Up:    spriteToUse = &snake.headUp;    break;
                case SnakeDirection::Left:  spriteToUse = &snake.headLeft;  break;
                case SnakeDirection::Down:  spriteToUse = &snake.headDown;  break;
                }
            }
            else if (i == snake.body.size() - 1)
            {
                Position2D tail = snake.body[i];
                Position2D prev = snake.body[i - 1];

                if (prev.x > tail.x)           spriteToUse = &snake.tailLeft;
                else if (prev.x < tail.x)      spriteToUse = &snake.tailRight;
                else if (prev.y > tail.y)      spriteToUse = &snake.tailUp;
                else if (prev.y < tail.y)      spriteToUse = &snake.tailDown;
            }
            else
            {
                Position2D prev = snake.body[i - 1];
                Position2D curr = snake.body[i];
                Position2D next = snake.body[i + 1];

                float toPrevX = curr.x - prev.x;
                float toPrevY = curr.y - prev.y;
                float toNextX = next.x - curr.x;
                float toNextY = next.y - curr.y;

                if (toPrevX == 0 && toNextX == 0)
                {
                    spriteToUse = &snake.bodyVertical;
                }
                else if (toPrevY == 0 && toNextY == 0)
                {
                    spriteToUse = &snake.bodyHorizontal;
                }
                else
                {
                    if (toPrevX < 0 && toNextY < 0)      spriteToUse = &snake.bodyTopRight;
                    else if (toPrevY > 0 && toNextX > 0) spriteToUse = &snake.bodyTopRight;
                    else if (toPrevX < 0 && toNextY > 0) spriteToUse = &snake.bodyBottomRight;
                    else if (toPrevY < 0 && toNextX > 0) spriteToUse = &snake.bodyBottomRight;
                    else if (toPrevX > 0 && toNextY < 0) spriteToUse = &snake.bodyTopLeft;
                    else if (toPrevY > 0 && toNextX < 0) spriteToUse = &snake.bodyTopLeft;
                    else if (toPrevX > 0 && toNextY > 0) spriteToUse = &snake.bodyBottomLeft;
                    else if (toPrevY < 0 && toNextX < 0) spriteToUse = &snake.bodyBottomLeft;
                }
            }

            if (spriteToUse)
            {
                spriteToUse->setPosition(snake.body[i].x, snake.body[i].y);
                window.draw(*spriteToUse);
            }
        }
    }
}
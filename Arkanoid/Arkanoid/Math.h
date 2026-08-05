#pragma once

namespace sf
{
    class Sprite;
}

namespace ArkanoidGame
{
    struct Vector2D
    {
        float x = 0;
        float y = 0;
    };

    typedef Vector2D Position2D;

    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
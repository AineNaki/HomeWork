#pragma once

namespace sf
{
    class Sprite;
}
namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0;
        float y = 0;
    };

    typedef Vector2D Position2D;

    Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight, float marginX = 0, float marginY = 0);

    bool IsCollide(Position2D pos1, float size1, Position2D pos2, float size2);

    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
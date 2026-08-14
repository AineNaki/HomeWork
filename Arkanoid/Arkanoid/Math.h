#pragma once

namespace sf
{
    class Sprite;
}

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
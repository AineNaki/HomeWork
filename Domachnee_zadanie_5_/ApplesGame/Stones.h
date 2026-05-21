#pragma once
#include "Math.h"
#include<SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
    struct Stone
    {
        Position2D position;
         sf::Sprite sprite;
    };

    void InitStone(Stone& stone, const sf::Texture& texture);
    void DrawStone(Stone& stone, sf::RenderWindow& window);
}
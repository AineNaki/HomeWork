#include"Stones.h"
#include "Game.h"

namespace ApplesGame
{
    void InitStone(Stone& stone, const sf::Texture& texture)
    {
        stone.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT, STONE_SIZE / 2, STONE_SIZE / 2);

        stone.sprite.setTexture(texture);
        SetSpriteSize(stone.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
        stone.sprite.setPosition(stone.position.x, stone.position.y);
    }

    void DrawStone(Stone& stone, sf::RenderWindow& window)
    {
        stone.sprite.setPosition(stone.position.x, stone.position.y);
        window.draw(stone.sprite);
    }



}